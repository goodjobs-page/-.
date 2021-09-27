// Copyright 2021 Google LLC
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
// source: generator/integration_tests/test.proto

#include "generator/integration_tests/golden/golden_kitchen_sink_connection.h"
#include "generator/integration_tests/golden/golden_kitchen_sink_options.h"
#include "generator/integration_tests/golden/internal/golden_kitchen_sink_option_defaults.h"
#include "generator/integration_tests/golden/internal/golden_kitchen_sink_stub_factory.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/resumable_streaming_read_rpc.h"
#include "google/cloud/internal/retry_loop.h"
#include "google/cloud/internal/streaming_read_rpc_logging.h"
#include <memory>

namespace google {
namespace cloud {
namespace golden {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

GoldenKitchenSinkConnection::~GoldenKitchenSinkConnection() = default;

StatusOr<google::test::admin::database::v1::GenerateAccessTokenResponse>
GoldenKitchenSinkConnection::GenerateAccessToken(
    google::test::admin::database::v1::GenerateAccessTokenRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::test::admin::database::v1::GenerateIdTokenResponse>
GoldenKitchenSinkConnection::GenerateIdToken(
    google::test::admin::database::v1::GenerateIdTokenRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StatusOr<google::test::admin::database::v1::WriteLogEntriesResponse>
GoldenKitchenSinkConnection::WriteLogEntries(
    google::test::admin::database::v1::WriteLogEntriesRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

StreamRange<std::string> GoldenKitchenSinkConnection::ListLogs(
    google::test::admin::database::v1::ListLogsRequest request) {
  return google::cloud::internal::MakePaginationRange<StreamRange<
    std::string>>(
    std::move(request),
    [](google::test::admin::database::v1::ListLogsRequest const&) {
      return StatusOr<google::test::admin::database::v1::ListLogsResponse>{};
    },
    [](google::test::admin::database::v1::ListLogsResponse const&) {
      return std::vector<std::string>();
    });
}

StreamRange<google::test::admin::database::v1::TailLogEntriesResponse> GoldenKitchenSinkConnection::TailLogEntries(
    google::test::admin::database::v1::TailLogEntriesRequest const&) {
  return google::cloud::internal::MakeStreamRange<
      google::test::admin::database::v1::TailLogEntriesResponse>(
      []() -> absl::variant<Status,
      google::test::admin::database::v1::TailLogEntriesResponse>{
        return Status(StatusCode::kUnimplemented, "not implemented");}
      );
}

StatusOr<google::test::admin::database::v1::ListServiceAccountKeysResponse>
GoldenKitchenSinkConnection::ListServiceAccountKeys(
    google::test::admin::database::v1::ListServiceAccountKeysRequest const&) {
  return Status(StatusCode::kUnimplemented, "not implemented");
}

namespace {
class GoldenKitchenSinkConnectionImpl : public GoldenKitchenSinkConnection {
 public:
  GoldenKitchenSinkConnectionImpl(
      std::shared_ptr<golden_internal::GoldenKitchenSinkStub> stub,
      Options const& options)
      : stub_(std::move(stub)),
        retry_policy_prototype_(options.get<GoldenKitchenSinkRetryPolicyOption>()->clone()),
        backoff_policy_prototype_(options.get<GoldenKitchenSinkBackoffPolicyOption>()->clone()),
        idempotency_policy_(options.get<GoldenKitchenSinkConnectionIdempotencyPolicyOption>()->clone()) {}

  ~GoldenKitchenSinkConnectionImpl() override = default;

  StatusOr<google::test::admin::database::v1::GenerateAccessTokenResponse>
  GenerateAccessToken(
      google::test::admin::database::v1::GenerateAccessTokenRequest const& request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->GenerateAccessToken(request),
        [this](grpc::ClientContext& context,
            google::test::admin::database::v1::GenerateAccessTokenRequest const& request) {
          return stub_->GenerateAccessToken(context, request);
        },
        request, __func__);
}

  StatusOr<google::test::admin::database::v1::GenerateIdTokenResponse>
  GenerateIdToken(
      google::test::admin::database::v1::GenerateIdTokenRequest const& request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->GenerateIdToken(request),
        [this](grpc::ClientContext& context,
            google::test::admin::database::v1::GenerateIdTokenRequest const& request) {
          return stub_->GenerateIdToken(context, request);
        },
        request, __func__);
}

  StatusOr<google::test::admin::database::v1::WriteLogEntriesResponse>
  WriteLogEntries(
      google::test::admin::database::v1::WriteLogEntriesRequest const& request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->WriteLogEntries(request),
        [this](grpc::ClientContext& context,
            google::test::admin::database::v1::WriteLogEntriesRequest const& request) {
          return stub_->WriteLogEntries(context, request);
        },
        request, __func__);
}

  StreamRange<std::string> ListLogs(
      google::test::admin::database::v1::ListLogsRequest request) override {
    request.clear_page_token();
    auto stub = stub_;
    auto retry =
        std::shared_ptr<GoldenKitchenSinkRetryPolicy const>(retry_policy_prototype_->clone());
    auto backoff = std::shared_ptr<BackoffPolicy const>(
        backoff_policy_prototype_->clone());
    auto idempotency = idempotency_policy_->ListLogs(request);
    char const* function_name = __func__;
    return google::cloud::internal::MakePaginationRange<StreamRange<
        std::string>>(
        std::move(request),
        [stub, retry, backoff, idempotency, function_name]
          (google::test::admin::database::v1::ListLogsRequest const& r) {
          return google::cloud::internal::RetryLoop(
              retry->clone(), backoff->clone(), idempotency,
              [stub](grpc::ClientContext& context,
                     google::test::admin::database::v1::ListLogsRequest const& request) {
                return stub->ListLogs(context, request);
              },
              r, function_name);
        },
        [](google::test::admin::database::v1::ListLogsResponse r) {
          std::vector<std::string> result(r.log_names().size());
          auto& messages = *r.mutable_log_names();
          std::move(messages.begin(), messages.end(), result.begin());
          return result;
        });
  }

  StreamRange<google::test::admin::database::v1::TailLogEntriesResponse> TailLogEntries(
      google::test::admin::database::v1::TailLogEntriesRequest const& request) override {
    auto stub = stub_;
    auto retry_policy =
        std::shared_ptr<GoldenKitchenSinkRetryPolicy const>(
            retry_policy_prototype_->clone());
    auto backoff_policy = std::shared_ptr<BackoffPolicy const>(
        backoff_policy_prototype_->clone());

    auto factory = [stub](
        google::test::admin::database::v1::TailLogEntriesRequest const& request) {
      return stub->TailLogEntries(absl::make_unique<grpc::ClientContext>(),
          request);
    };

    auto resumable =
        internal::MakeResumableStreamingReadRpc<
            google::test::admin::database::v1::TailLogEntriesResponse,
            google::test::admin::database::v1::TailLogEntriesRequest>(
                retry_policy->clone(), backoff_policy->clone(),
                [](std::chrono::milliseconds) {}, factory,
                GoldenKitchenSinkTailLogEntriesStreamingUpdater,
                request);

    return internal::MakeStreamRange(internal::StreamReader<
        google::test::admin::database::v1::TailLogEntriesResponse>(
        [resumable]{return resumable->Read();}));
  }

  StatusOr<google::test::admin::database::v1::ListServiceAccountKeysResponse>
  ListServiceAccountKeys(
      google::test::admin::database::v1::ListServiceAccountKeysRequest const& request) override {
    return google::cloud::internal::RetryLoop(
        retry_policy_prototype_->clone(), backoff_policy_prototype_->clone(),
        idempotency_policy_->ListServiceAccountKeys(request),
        [this](grpc::ClientContext& context,
            google::test::admin::database::v1::ListServiceAccountKeysRequest const& request) {
          return stub_->ListServiceAccountKeys(context, request);
        },
        request, __func__);
}

 private:
  std::shared_ptr<golden_internal::GoldenKitchenSinkStub> stub_;
  std::unique_ptr<GoldenKitchenSinkRetryPolicy const> retry_policy_prototype_;
  std::unique_ptr<BackoffPolicy const> backoff_policy_prototype_;
  std::unique_ptr<GoldenKitchenSinkConnectionIdempotencyPolicy> idempotency_policy_;
};
}  // namespace

std::shared_ptr<GoldenKitchenSinkConnection> MakeGoldenKitchenSinkConnection(
    Options options) {
  options = golden_internal::GoldenKitchenSinkDefaultOptions(
      std::move(options));
  return std::make_shared<GoldenKitchenSinkConnectionImpl>(
      golden_internal::CreateDefaultGoldenKitchenSinkStub(options), options);
}

std::shared_ptr<GoldenKitchenSinkConnection> MakeGoldenKitchenSinkConnection(
    std::shared_ptr<golden_internal::GoldenKitchenSinkStub> stub,
    Options options) {
  options = golden_internal::GoldenKitchenSinkDefaultOptions(
      std::move(options));
  return std::make_shared<GoldenKitchenSinkConnectionImpl>(
      std::move(stub), std::move(options));
}

}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace golden
}  // namespace cloud
}  // namespace google

