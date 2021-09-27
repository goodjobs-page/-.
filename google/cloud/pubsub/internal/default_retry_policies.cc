// Copyright 2020 Google LLC
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

#include "google/cloud/pubsub/internal/default_retry_policies.h"
#include "absl/memory/memory.h"

namespace google {
namespace cloud {
namespace pubsub_internal {
inline namespace GOOGLE_CLOUD_CPP_PUBSUB_NS {

std::unique_ptr<pubsub::RetryPolicy const> DefaultRetryPolicy() {
  return absl::make_unique<pubsub::LimitedTimeRetryPolicy>(
      std::chrono::seconds(60));
}

std::unique_ptr<pubsub::BackoffPolicy const> DefaultBackoffPolicy() {
  return absl::make_unique<pubsub::ExponentialBackoffPolicy>(
      std::chrono::milliseconds(100), std::chrono::seconds(60), 1.3);
}

}  // namespace GOOGLE_CLOUD_CPP_PUBSUB_NS
}  // namespace pubsub_internal
}  // namespace cloud
}  // namespace google
