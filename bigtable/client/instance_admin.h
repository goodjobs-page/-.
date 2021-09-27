// Copyright 2018 Google Inc.
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

#ifndef GOOGLE_CLOUD_CPP_BIGTABLE_CLIENT_INSTANCE_ADMIN_H_
#define GOOGLE_CLOUD_CPP_BIGTABLE_CLIENT_INSTANCE_ADMIN_H_

#include "bigtable/client/instance_admin_client.h"
#include "bigtable/client/internal/instance_admin.h"
#include "bigtable/client/internal/unary_rpc_utils.h"
#include <memory>

namespace bigtable {
inline namespace BIGTABLE_CLIENT_NS {
/**
 * Implements a minimal API to administer Cloud Bigtable instances.
 */
class InstanceAdmin {
 public:
  /**
   * @param client the interface to create grpc stubs, report errors, etc.
   */
  InstanceAdmin(std::shared_ptr<InstanceAdminClient> client)
      : impl_(std::move(client)) {}

  /**
   * Create a new InstanceAdmin using explicit policies to handle RPC errors.
   *
   * @tparam RPCRetryPolicy control which operations to retry and for how long.
   * @tparam RPCBackoffPolicy control how does the client backs off after an RPC
   *     error.
   * @param client the interface to create grpc stubs, report errors, etc.
   * @param retry_policy the policy to handle RPC errors.
   * @param backoff_policy the policy to control backoff after an error.
   */
  template <typename RPCRetryPolicy, typename RPCBackoffPolicy>
  InstanceAdmin(std::shared_ptr<InstanceAdminClient> client,
                RPCRetryPolicy retry_policy, RPCBackoffPolicy backoff_policy)
      : impl_(std::move(client), std::move(retry_policy),
              std::move(backoff_policy)) {}

  /// The full name (`projects/<project_id>`) of the project.
  std::string const& project_name() const { return impl_.project_name(); }
  /// The project id, i.e., `project_name()` without the `projects/` prefix.
  std::string const& project_id() const { return impl_.project_id(); }

  /**
   * Return the list of instances in the project.
   * @return
   */
  std::vector<::google::bigtable::admin::v2::Instance> ListInstances();

  InstanceAdmin(InstanceAdmin const&) = delete;
  InstanceAdmin operator=(InstanceAdmin const&) = delete;

 private:
  noex::InstanceAdmin impl_;
};

}  // namespace BIGTABLE_CLIENT_NS
}  // namespace bigtable

#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_CLIENT_INSTANCE_ADMIN_H_
