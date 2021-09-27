// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/iam/credentials/v1/iamcredentials.proto

#include "google/cloud/iam/iam_credentials_connection.h"
#include "google/cloud/iam/iam_credentials_options.h"
#include "google/cloud/iam/internal/iam_credentials_option_defaults.h"
#include "google/cloud/iam/internal/iam_credentials_stub_factory.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>

namespace google {
namespace cloud {
namespace iam {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

IAMCredentialsConnection::~IAMCredentialsConnection() = default;

StatusOr<google::iam::credentials::v1::GenerateAccessTokenResponse>
IAMCredentialsConnection::GenerateAccessToken(
    google::iam::credentials::v1::GenerateAccessTokenRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::credentials::v1::GenerateIdTokenResponse>
IAMCredentialsConnection::GenerateIdToken(
    google::iam::credentials::v1::GenerateIdTokenRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::credentials::v1::SignBlobResponse>
IAMCredentialsConnection::SignBlob(
    google::iam::credentials::v1::SignBlobRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::iam::credentials::v1::SignJwtResponse>
IAMCredentialsConnection::SignJwt(
    google::iam::credentials::v1::SignJwtRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

namespace {
class IAMCredentialsConnectionImpl : public IAMCredentialsConnection {
 public:
  IAMCredentialsConnectionImpl(
      std::unique_ptr<google::cloud::BackgroundThreads> background,
      std::shared_ptr<iam_internal::IAMCredentialsStub> stub,
      Options const& options)
      : background_(std::move(background)),
        stub_(std::move(stub)),
        retry_policy_prototype_(
            options.get<IAMCredentialsRetryPolicyOption>()->clone()),
        backoff_policy_prototype_(
            options.get<IAMCredentialsBackoffPolicyOption>()->clone()),
        idempotency_policy_(
            options.get<IAMCredentialsConnectionIdempotencyPolicyOption>()
                ->clone()) {}

  ~IAMCredentialsConnectionImpl() override = default;

  StatusOr<google::iam::credentials::v1::GenerateAccessTokenResponse>
  GenerateAccessToken(
      google::iam::credentials::v1::GenerateAccessTokenRequest const& request)
      override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->GenerateAccessToken(request),
        [this](grpc::ClientContext& context,
               google::iam::credentials::v1::GenerateAccessTokenRequest const&
                   request) {
          return stub_->GenerateAccessToken(context, request);
        },
        request, __func__);
  }

  StatusOr<google::iam::credentials::v1::GenerateIdTokenResponse>
  GenerateIdToken(google::iam::credentials::v1::GenerateIdTokenRequest const&
                      request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->GenerateIdToken(request),
        [this](grpc::ClientContext& context,
               google::iam::credentials::v1::GenerateIdTokenRequest const&
                   request) {
          return stub_->GenerateIdToken(context, request);
        },
        request, __func__);
  }

  StatusOr<google::iam::credentials::v1::SignBlobResponse> SignBlob(
      google::iam::credentials::v1::SignBlobRequest const& request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->SignBlob(request),
        [this](grpc::ClientContext& context,
               google::iam::credentials::v1::SignBlobRequest const& request) {
          return stub_->SignBlob(context, request);
        },
        request, __func__);
  }

  StatusOr<google::iam::credentials::v1::SignJwtResponse> SignJwt(
      google::iam::credentials::v1::SignJwtRequest const& request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->SignJwt(request),
        [this](grpc::ClientContext& context,
               google::iam::credentials::v1::SignJwtRequest const& request) {
          return stub_->SignJwt(context, request);
        },
        request, __func__);
  }

 private:
  std::unique_ptr<google::cloud::BackgroundThreads> background_;
  std::shared_ptr<iam_internal::IAMCredentialsStub> stub_;
  std::unique_ptr<IAMCredentialsRetryPolicy const> retry_policy_prototype_;
  std::unique_ptr<BackoffPolicy const> backoff_policy_prototype_;
  std::unique_ptr<IAMCredentialsConnectionIdempotencyPolicy>
      idempotency_policy_;
};
}  // namespace

std::shared_ptr<IAMCredentialsConnection> MakeIAMCredentialsConnection(
    Options options) {
  options = iam_internal::IAMCredentialsDefaultOptions(std::move(options));
  auto background = internal::MakeBackgroundThreadsFactory(options)();
  auto stub =
      iam_internal::CreateDefaultIAMCredentialsStub(background->cq(), options);
  return std::make_shared<IAMCredentialsConnectionImpl>(
      std::move(background), std::move(stub), options);
}

}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace iam
}  // namespace cloud
}  // namespace google

namespace google {
namespace cloud {
namespace iam_internal {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

std::shared_ptr<iam::IAMCredentialsConnection> MakeIAMCredentialsConnection(
    std::shared_ptr<IAMCredentialsStub> stub, Options options) {
  options = IAMCredentialsDefaultOptions(std::move(options));
  return std::make_shared<iam::IAMCredentialsConnectionImpl>(
      internal::MakeBackgroundThreadsFactory(options)(), std::move(stub),
      std::move(options));
}

}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace iam_internal
}  // namespace cloud
}  // namespace google
