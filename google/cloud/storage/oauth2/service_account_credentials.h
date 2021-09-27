// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_OAUTH2_SERVICE_ACCOUNT_CREDENTIALS_H_
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_OAUTH2_SERVICE_ACCOUNT_CREDENTIALS_H_

#include "google/cloud/optional.h"
#include "google/cloud/storage/internal/curl_request_builder.h"
#include "google/cloud/storage/internal/nljson.h"
#include "google/cloud/storage/internal/openssl_util.h"
#include "google/cloud/storage/internal/sha256_hash.h"
#include "google/cloud/storage/oauth2/credential_constants.h"
#include "google/cloud/storage/oauth2/credentials.h"
#include "google/cloud/storage/oauth2/refreshing_credentials_wrapper.h"
#include <condition_variable>
#include <ctime>
#include <iostream>
#include <mutex>
#include <set>

namespace google {
namespace cloud {
namespace storage {
inline namespace STORAGE_CLIENT_NS {
namespace oauth2 {
/// Object to hold information used to instantiate an ServiceAccountCredentials.
struct ServiceAccountCredentialsInfo {
  std::string client_email;
  std::string private_key_id;
  std::string private_key;
  std::string token_uri;
  // If no set is supplied, a default set of scopes will be used.
  google::cloud::optional<std::set<std::string>> scopes;
  // See https://developers.google.com/identity/protocols/OAuth2ServiceAccount.
  google::cloud::optional<std::string> subject;
};

/// Parses the contents of a JSON keyfile into a ServiceAccountCredentialsInfo.
StatusOr<ServiceAccountCredentialsInfo> ParseServiceAccountCredentials(
    std::string const& content, std::string const& source,
    std::string const& default_token_uri = GoogleOAuthRefreshEndpoint());

/**
 * Wrapper class for Google OAuth 2.0 service account credentials.
 *
 * Takes a ServiceAccountCredentialsInfo and obtains access tokens from the
 * Google Authorization Service as needed.  Instances of this class should
 * usually be created via the convenience methods declared in
 * google_credentials.h.
 *
 * An HTTP Authorization header, with an access token as its value,
 * can be obtained by calling the AuthorizationHeader() method; if the current
 * access token is invalid or nearing expiration, this will class will first
 * obtain a new access token before returning the Authorization header string.

 * @see https://developers.google.com/identity/protocols/OAuth2ServiceAccount
 * for an overview of using service accounts with Google's OAuth 2.0 system.
 *
 * @see https://cloud.google.com/storage/docs/reference/libraries for details on
 * how to obtain and get started with service account credentials.
 *
 * @tparam HttpRequestBuilderType a dependency injection point. It makes it
 *     possible to mock internal libcurl wrappers. This should generally not be
 *     overridden except for testing.
 * @tparam ClockType a dependency injection point to fetch the current time.
 *     This should generally not be overridden except for testing.
 */
template <typename HttpRequestBuilderType =
              storage::internal::CurlRequestBuilder,
          typename ClockType = std::chrono::system_clock>
class ServiceAccountCredentials : public Credentials {
 public:
  explicit ServiceAccountCredentials(ServiceAccountCredentialsInfo const& info)
      : clock_() {
    namespace nl = storage::internal::nl;

    HttpRequestBuilderType request_builder(
        info.token_uri, storage::internal::GetDefaultCurlHandleFactory());
    auto assertion_components = std::move(AssertionComponentsFromInfo(info));
    // This is the value of grant_type for JSON-formatted service account
    // keyfiles downloaded from Cloud Console.
    std::string payload("grant_type=");
    payload +=
        request_builder
            .MakeEscapedString("urn:ietf:params:oauth:grant-type:jwt-bearer")
            .get();
    payload += "&assertion=";
    payload += MakeJWTAssertion(assertion_components.first,
                                assertion_components.second, info.private_key);
    payload_ = std::move(payload);

    request_builder.AddHeader(
        "Content-Type: application/x-www-form-urlencoded");
    request_ = request_builder.BuildRequest();
    info_ = info;
  }

  StatusOr<std::string> AuthorizationHeader() override {
    std::unique_lock<std::mutex> lock(mu_);
    return refreshing_creds_.AuthorizationHeader([this] { return Refresh(); });
  }

  /**
   * Create a RSA SHA256 signature of the blob using the Credential object.
   *
   * @param signing_account the desired service account which should sign
   *   @p blob. If not set, uses this object's account. If set, it must match
   *   this object's service account.
   * @param blob the string to sign. Note that sometimes the application must
   *   Base64-encode the data before signing.
   * @return the signed blob as raw bytes. An error if the @p signing_account
   *     does not match the email for the credential's account.
   */
  StatusOr<std::vector<std::uint8_t>> SignBlob(
      SigningAccount const& signing_account,
      std::string const& blob) const override {
    if (signing_account.has_value() &&
        signing_account.value() != info_.client_email) {
      return Status(StatusCode::kInvalidArgument,
                    "The current_credentials cannot sign blobs for " +
                        signing_account.value());
    }
    return internal::SignStringWithPem(blob, info_.private_key,
                                       JwtSigningAlgorithms::RS256);
  }

  std::string AccountEmail() const override { return info_.client_email; }
  std::string KeyId() const override { return info_.private_key_id; }

 private:
  /**
   * Returns the header and payload components needed to make a JWT assertion.
   *
   * @see
   * https://cloud.google.com/endpoints/docs/frameworks/java/troubleshoot-jwt
   *
   * @see https://tools.ietf.org/html/rfc7523
   */
  std::pair<storage::internal::nl::json, storage::internal::nl::json>
  AssertionComponentsFromInfo(ServiceAccountCredentialsInfo const& info) {
    namespace nl = storage::internal::nl;
    nl::json assertion_header = {
        {"alg", "RS256"}, {"kid", info.private_key_id}, {"typ", "JWT"}};

    // Scopes must be specified in a comma-delimited string.
    std::string scope_str;
    if (!info.scopes) {
      scope_str = GoogleOAuthScopeCloudPlatform();
    } else {
      std::string sep = "";
      for (const auto& scope : *(info.scopes)) {
        scope_str += sep + scope;
        sep = ",";
      }
    }

    auto now = clock_.now();
    auto expiration = now + GoogleOAuthAccessTokenLifetime();
    // As much as possible, do the time arithmetic using the std::chrono types.
    // Convert to longs only when we are dealing with timestamps since the
    // epoch.
    auto now_from_epoch =
        static_cast<long>(std::chrono::system_clock::to_time_t(now));
    auto expiration_from_epoch =
        static_cast<long>(std::chrono::system_clock::to_time_t(expiration));
    nl::json assertion_payload = {
        {"iss", info.client_email},
        {"scope", scope_str},
        {"aud", info.token_uri},
        {"iat", now_from_epoch},
        // Resulting access token should be expire after one hour.
        {"exp", expiration_from_epoch}};
    if (info.subject) {
      assertion_payload["sub"] = *(info.subject);
    }

    return std::make_pair(std::move(assertion_header),
                          std::move(assertion_payload));
  }

  /**
   * Given a key and a JSON header and payload, creates a JWT assertion string.
   *
   * @see https://tools.ietf.org/html/rfc7519
   */
  std::string MakeJWTAssertion(storage::internal::nl::json const& header,
                               storage::internal::nl::json const& payload,
                               std::string const& pem_contents) {
    std::string encoded_header = internal::UrlsafeBase64Encode(header.dump());
    std::string encoded_payload = internal::UrlsafeBase64Encode(payload.dump());
    std::string encoded_signature = internal::UrlsafeBase64Encode(
        internal::SignStringWithPem(encoded_header + '.' + encoded_payload,
                                    pem_contents, JwtSigningAlgorithms::RS256));
    return encoded_header + '.' + encoded_payload + '.' + encoded_signature;
  }

  Status Refresh() {
    namespace nl = storage::internal::nl;

    auto response = request_.MakeRequest(payload_);
    if (!response) {
      return std::move(response).status();
    }
    if (response->status_code >= 300) {
      return AsStatus(*response);
    }

    nl::json access_token = nl::json::parse(response->payload, nullptr, false);
    if (access_token.is_discarded() ||
        access_token.count("access_token") == 0U or
        access_token.count("expires_in") == 0U or
        access_token.count("token_type") == 0U) {
      response->payload +=
          "Could not find all required fields in response (access_token,"
          " expires_in, token_type).";
      return AsStatus(*response);
    }
    // Response should have the attributes "access_token", "expires_in", and
    // "token_type".
    std::string header =
        "Authorization: " + access_token.value("token_type", "") + " " +
        access_token.value("access_token", "");
    auto expires_in =
        std::chrono::seconds(access_token.value("expires_in", int(0)));
    auto new_expiration = std::chrono::system_clock::now() + expires_in;
    // Do not update any state until all potential exceptions are raised.
    refreshing_creds_.authorization_header = std::move(header);
    refreshing_creds_.expiration_time = new_expiration;
    return Status();
  }

  typename HttpRequestBuilderType::RequestType request_;
  std::string payload_;
  ServiceAccountCredentialsInfo info_;
  mutable std::mutex mu_;
  RefreshingCredentialsWrapper refreshing_creds_;
  ClockType clock_;
};

}  // namespace oauth2
}  // namespace STORAGE_CLIENT_NS
}  // namespace storage
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_OAUTH2_SERVICE_ACCOUNT_CREDENTIALS_H_
