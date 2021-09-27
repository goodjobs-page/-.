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
#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_BIGQUERY_READ_CONNECTION_IDEMPOTENCY_POLICY_GCPCXX_PB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_BIGQUERY_READ_CONNECTION_IDEMPOTENCY_POLICY_GCPCXX_PB_H

#include "google/cloud/internal/retry_policy.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/cloud/bigquery/storage/v1/storage.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace bigquery {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

class BigQueryReadConnectionIdempotencyPolicy {
 public:
  virtual ~BigQueryReadConnectionIdempotencyPolicy() = 0;

  /// Create a new copy of this object.
  virtual std::unique_ptr<BigQueryReadConnectionIdempotencyPolicy> clone()
      const = 0;

  virtual google::cloud::internal::Idempotency CreateReadSession(
      ::google::cloud::bigquery::storage::v1::CreateReadSessionRequest const&
          request) = 0;

  virtual google::cloud::internal::Idempotency SplitReadStream(
      ::google::cloud::bigquery::storage::v1::SplitReadStreamRequest const&
          request) = 0;
};

std::unique_ptr<BigQueryReadConnectionIdempotencyPolicy>
MakeDefaultBigQueryReadConnectionIdempotencyPolicy();

}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace bigquery
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_BIGQUERY_READ_CONNECTION_IDEMPOTENCY_POLICY_GCPCXX_PB_H
