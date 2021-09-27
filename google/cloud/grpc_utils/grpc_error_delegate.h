// Copyright 2019 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_GRPC_UTILS_GRPC_ERROR_DELEGATE_H_
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_GRPC_UTILS_GRPC_ERROR_DELEGATE_H_

#include "google/cloud/grpc_utils/version.h"
#include "google/cloud/status.h"
#include <google/rpc/status.pb.h>
#include <grpcpp/grpcpp.h>

namespace google {
namespace cloud {
namespace grpc_utils {
inline namespace GOOGLE_CLOUD_CPP_GRPC_UTILS_NS {
/**
 * Creates a google::cloud::Status from a grpc::Status.
 */
google::cloud::Status MakeStatusFromRpcError(grpc::Status const& status);

/**
 * Creates a google::cloud::Status from a grpc::StatusCode and description.
 */
google::cloud::Status MakeStatusFromRpcError(grpc::StatusCode code,
                                             std::string what);

/**
 * Creates a `google::cloud::Status` from a `google:rpc::Status` proto.
 *
 * Some gRPC services return the `google::rpc::Status` proto for errors. The
 * libraries in `google-cloud-cpp` represent these errors using a
 * `google::cloud::Status`.
 */
google::cloud::Status MakeStatusFromRpcError(google::rpc::Status const& status);

}  // namespace GOOGLE_CLOUD_CPP_GRPC_UTILS_NS
}  // namespace grpc_utils
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_GRPC_UTILS_GRPC_ERROR_DELEGATE_H_
