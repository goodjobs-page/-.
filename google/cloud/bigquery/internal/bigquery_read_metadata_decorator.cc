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
// source: google/cloud/bigquery/storage/v1/storage.proto
#include "google/cloud/bigquery/internal/bigquery_read_metadata_decorator.h"
#include "google/cloud/internal/api_client_header.h"
#include "google/cloud/status_or.h"
#include <google/cloud/bigquery/storage/v1/storage.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace bigquery_internal {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

BigQueryReadMetadata::BigQueryReadMetadata(
    std::shared_ptr<BigQueryReadStub> child)
    : child_(std::move(child)),
      api_client_header_(google::cloud::internal::ApiClientHeader()) {}

StatusOr<::google::cloud::bigquery::storage::v1::ReadSession>
BigQueryReadMetadata::CreateReadSession(
    grpc::ClientContext& context,
    ::google::cloud::bigquery::storage::v1::CreateReadSessionRequest const&
        request) {
  SetMetadata(context, "read_session.table=" + request.read_session().table());
  return child_->CreateReadSession(context, request);
}

std::unique_ptr<internal::StreamingReadRpc<
    ::google::cloud::bigquery::storage::v1::ReadRowsResponse>>
BigQueryReadMetadata::ReadRows(
    std::unique_ptr<grpc::ClientContext> context,
    ::google::cloud::bigquery::storage::v1::ReadRowsRequest const& request) {
  SetMetadata(*context, "read_stream=" + request.read_stream());
  return child_->ReadRows(std::move(context), request);
}

StatusOr<::google::cloud::bigquery::storage::v1::SplitReadStreamResponse>
BigQueryReadMetadata::SplitReadStream(
    grpc::ClientContext& context,
    ::google::cloud::bigquery::storage::v1::SplitReadStreamRequest const&
        request) {
  SetMetadata(context, "name=" + request.name());
  return child_->SplitReadStream(context, request);
}

void BigQueryReadMetadata::SetMetadata(grpc::ClientContext& context,
                                       std::string const& request_params) {
  context.AddMetadata("x-goog-request-params", request_params);
  context.AddMetadata("x-goog-api-client", api_client_header_);
}

}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace bigquery_internal
}  // namespace cloud
}  // namespace google
