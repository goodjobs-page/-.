// Copyright 2017 Google Inc.
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_TABLE_ADMIN_H_
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_TABLE_ADMIN_H_

#include "google/cloud/bigtable/admin_client.h"
#include "google/cloud/bigtable/bigtable_strong_types.h"
#include "google/cloud/bigtable/column_family.h"
#include "google/cloud/bigtable/internal/grpc_error_delegate.h"
#include "google/cloud/bigtable/internal/table_admin.h"
#include "google/cloud/bigtable/polling_policy.h"
#include "google/cloud/bigtable/table_config.h"
#include "google/cloud/future.h"
#include "google/cloud/status_or.h"
#include <future>
#include <memory>

namespace google {
namespace cloud {
namespace bigtable {
inline namespace BIGTABLE_CLIENT_NS {
enum class Consistency { kConsistent, kInconsistent };

/**
 * Implements the API to administer tables in a Cloud Bigtable instance.
 */
class TableAdmin {
 public:
  /**
   * @param client the interface to create grpc stubs, report errors, etc.
   * @param instance_id the id of the instance, e.g., "my-instance", the full
   *   name (e.g. '/projects/my-project/instances/my-instance') is built using
   *   the project id in the @p client parameter.
   *
   * @par Cost
   * Creating a new object of type `TableAdmin` is comparable to creating a few
   * objects of type `std::string` or a few objects of type
   * `std::shared_ptr<int>`. The class represents a shallow handle to a remote
   * object.
   */
  TableAdmin(std::shared_ptr<AdminClient> client, std::string instance_id)
      : impl_(std::move(client), std::move(instance_id)) {}

  /**
   * Create a new TableAdmin using explicit policies to handle RPC errors.
   *
   * @param client the interface to create grpc stubs, report errors, etc.
   * @param instance_id the id of the instance, e.g., "my-instance", the full
   *   name (e.g. '/projects/my-project/instances/my-instance') is built using
   *   the project id in the @p client parameter.
   * @param policies the set of policy overrides for this object.
   * @tparam Policies the types of the policies to override, the types must
   *     derive from one of the following types:
   *     - `RPCBackoffPolicy` how to backoff from a failed RPC. Currently only
   *       `ExponentialBackoffPolicy` is implemented. You can also create your
   *       own policies that backoff using a different algorithm.
   *     - `RPCRetryPolicy` for how long to retry failed RPCs. Use
   *       `LimitedErrorCountRetryPolicy` to limit the number of failures
   *       allowed. Use `LimitedTimeRetryPolicy` to bound the time for any
   *       request. You can also create your own policies that combine time and
   *       error counts.
   *     - `PollingPolicy` for how long will the class wait for
   *       `google.longrunning.Operation` to complete. This class combines both
   *       the backoff policy for checking long running operations and the
   *       retry policy.
   *
   * @see GenericPollingPolicy, ExponentialBackoffPolicy,
   *     LimitedErrorCountRetryPolicy, LimitedTimeRetryPolicy.
   */
  template <typename... Policies>
  TableAdmin(std::shared_ptr<AdminClient> client, std::string instance_id,
             Policies&&... policies)
      : impl_(std::move(client), std::move(instance_id),
              std::forward<Policies>(policies)...) {}

  TableAdmin(TableAdmin const& table_admin) = default;
  TableAdmin& operator=(TableAdmin const& table_admin) = default;

  std::string const& project() const { return impl_.project(); }
  std::string const& instance_id() const { return impl_.instance_id(); }
  std::string const& instance_name() const { return impl_.instance_name(); }

  /**
   * Create a new table in the instance.
   *
   * @param table_id the name of the table relative to the instance managed by
   *     this object.  The full table name is
   *     `projects/<PROJECT_ID>/instances/<INSTANCE_ID>/tables/<table_id>`
   *     where PROJECT_ID is obtained from the associated AdminClient and
   *     INSTANCE_ID is the instance_id() of this object.
   * @param config the initial schema for the table.
   * @return the attributes of the newly created table.  Notice that the server
   *     only populates the table_name() field at this time.
   *
   * @par Example
   * @snippet table_admin_snippets.cc create table
   */
  StatusOr<::google::bigtable::admin::v2::Table> CreateTable(
      std::string table_id, TableConfig config);

  /**
   * Sends an asynchronous request to create a new table in the instance.
   *
   * @warning This is an early version of the asynchronous APIs for Cloud
   *     Bigtable. These APIs might be changed in backward-incompatible ways. It
   *     is not subject to any SLA or deprecation policy.
   *
   * @param table_id the name of the table relative to the instance managed by
   *     this object.  The full table name is
   *     `projects/<PROJECT_ID>/instances/<INSTANCE_ID>/tables/<table_id>`
   *     where PROJECT_ID is obtained from the associated AdminClient and
   *     INSTANCE_ID is the instance_id() of this object.
   * @param config the initial schema for the table.
   * @param cq the completion queue that will execute the asynchronous calls,
   *     the application must ensure that one or more threads are blocked on
   *     `cq.Run()`.
   *
   * @return a future that will be satisfied when the request succeeds or the
   *   retry policy expires.  In the first case, the future will contain the
   *   response from the service. In the second the future is satisfied with
   *   an exception. Note that the service only fills out the `table_name` field
   *   for this request.
   *
   * @throws std::exception if the operation cannot be started.
   *
   * @par Example
   * @snippet table_admin_async_snippets.cc async create table
   */
  future<StatusOr<google::bigtable::admin::v2::Table>> AsyncCreateTable(
      CompletionQueue& cq, std::string table_id, TableConfig config);

  /**
   * Return all the tables in the instance.
   *
   * @param view define what information about the tables is retrieved.
   *   - `VIEW_UNSPECIFIED`: equivalent to `VIEW_SCHEMA`.
   *   - `NAME`: return only the name of the table.
   *   - `VIEW_SCHEMA`: return the name and the schema.
   *   - `FULL`: return all the information about the table.
   *
   * @par Example
   * @snippet table_admin_snippets.cc list tables
   */
  StatusOr<std::vector<::google::bigtable::admin::v2::Table>> ListTables(
      ::google::bigtable::admin::v2::Table::View view);

  /**
   * Get information about a single table.
   *
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   * @param view describes how much information to get about the name.
   *   - VIEW_UNSPECIFIED: equivalent to VIEW_SCHEMA.
   *   - NAME: return only the name of the table.
   *   - VIEW_SCHEMA: return the name and the schema.
   *   - FULL: return all the information about the table.
   * @return the information about the table or status.
   *
   * @par Example
   * @snippet table_admin_snippets.cc get table
   */
  StatusOr<::google::bigtable::admin::v2::Table> GetTable(
      std::string const& table_id,
      ::google::bigtable::admin::v2::Table::View view =
          ::google::bigtable::admin::v2::Table::SCHEMA_VIEW);

  /**
   * Sends an asynchronous request to get information about an existing table.
   *
   * @warning This is an early version of the asynchronous APIs for Cloud
   *     Bigtable. These APIs might be changed in backward-incompatible ways. It
   *     is not subject to any SLA or deprecation policy.
   *
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   * @param view describes how much information to get about the name.
   *   - VIEW_UNSPECIFIED: equivalent to VIEW_SCHEMA.
   *   - NAME: return only the name of the table.
   *   - VIEW_SCHEMA: return the name and the schema.
   *   - FULL: return all the information about the table.
   * @param cq the completion queue that will execute the asynchronous calls,
   *     the application must ensure that one or more threads are blocked on
   *     `cq.Run()`.
   *
   * @return a future that will be satisfied when the request succeeds or the
   *   retry policy expires. In the first case, the future will contain the
   *   response from the service. In the second the future is satisfied with
   *   an exception.
   *
   * @throws std::exception if the operation cannot be started.
   *
   * @par Example
   * @snippet table_admin_async_snippets.cc async get table
   */
  future<StatusOr<google::bigtable::admin::v2::Table>> AsyncGetTable(
      CompletionQueue& cq, std::string const& table_id,
      google::bigtable::admin::v2::Table::View view);

  /**
   * Delete a table.
   *
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   *
   * @return status of the operation.
   *
   * @par Example
   * @snippet table_admin_snippets.cc delete table
   */
  Status DeleteTable(std::string const& table_id);

  /**
   * Start a request to asynchronously delete a table.
   *
   * @warning This is an early version of the asynchronous APIs for Cloud
   *     Bigtable. These APIs might be changed in backward-incompatible ways. It
   *     is not subject to any SLA or deprecation policy.
   *
   * @param cq the completion queue that will execute the asynchronous calls,
   *     the application must ensure that one or more threads are blocked on
   *     `cq.Run()`.
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   *
   * @return status of the operation.
   *
   * @par Example
   * @snippet table_admin_async_snippets.cc async delete table
   */
  future<Status> AsyncDeleteTable(CompletionQueue& cq,
                                  std::string const& table_id);

  /**
   * Modify the schema for an existing table.
   *
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   * @param modifications the list of modifications to the schema.
   *
   * @par Example
   * @snippet table_admin_snippets.cc modify table
   */
  StatusOr<::google::bigtable::admin::v2::Table> ModifyColumnFamilies(
      std::string const& table_id,
      std::vector<ColumnFamilyModification> modifications);

  /**
   * Make an asynchronous request to modify the column families of a table.
   *
   * @warning This is an early version of the asynchronous APIs for Cloud
   *     Bigtable. These APIs might be changed in backward-incompatible ways. It
   *     is not subject to any SLA or deprecation policy.
   *
   * @param cq the completion queue that will execute the asynchronous calls,
   *     the application must ensure that one or more threads are blocked on
   *     `cq.Run()`.
   * @param table_id the name of the table relative to the instance managed by
   *     this object.  The full table name is
   *     `projects/<PROJECT_ID>/instances/<INSTANCE_ID>/tables/<table_id>`
   *     where PROJECT_ID is obtained from the associated AdminClient and
   *     INSTANCE_ID is the instance_id() of this object.
   * @param modifications the list of modifications to the schema.
   * @return the information about table or status.
   *
   * @par Example
   * @snippet table_admin_async_snippets.cc async modify table
   */
  future<StatusOr<::google::bigtable::admin::v2::Table>>
  AsyncModifyColumnFamilies(
      CompletionQueue& cq, std::string const& table_id,
      std::vector<ColumnFamilyModification> modifications);

  /**
   * Delete all the rows that start with a given prefix.
   *
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   * @param row_key_prefix drop any rows that start with this prefix.
   *
   * @par Example
   * @snippet table_admin_snippets.cc drop rows by prefix
   */
  Status DropRowsByPrefix(std::string const& table_id,
                          std::string row_key_prefix);

  /**
   * Generates consistency token for a table.
   *
   * @param table_id the id of the table for which we want to generate
   *     consistency token.
   * @return the consistency token for table.
   *
   * @par Example
   * @snippet table_admin_snippets.cc generate consistency token
   */
  StatusOr<ConsistencyToken> GenerateConsistencyToken(
      std::string const& table_id);

  /**
   * Checks consistency of a table.
   *
   * @param table_id  the id of the table for which we want to check
   *     consistency.
   * @param consistency_token the consistency token of the table.
   * @return the consistency status for the table.
   *
   * @par Example
   * @snippet table_admin_snippets.cc check consistency
   */
  StatusOr<Consistency> CheckConsistency(
      bigtable::TableId const& table_id,
      bigtable::ConsistencyToken const& consistency_token);

  /**
   * Checks consistency of a table with multiple calls using a separate thread
   *
   * @param table_id the id of the table for which we want to check
   *     consistency.
   * @param consistency_token the consistency token of the table.
   * @return the consistency status for the table.
   * @throws std::exception if the operation cannot be completed.
   *
   * @par Example
   * @snippet table_admin_snippets.cc wait for consistency check
   */
  std::future<StatusOr<bool>> WaitForConsistencyCheck(
      bigtable::TableId const& table_id,
      bigtable::ConsistencyToken const& consistency_token) {
    return std::async(std::launch::async,
                      &TableAdmin::WaitForConsistencyCheckImpl, this, table_id,
                      consistency_token);
  }

  /**
   * Delete all the rows in a table.
   *
   * @param table_id the id of the table within the instance associated with
   *     this object. The full name of the table is
   *     `this->instance_name() + "/tables/" + table_id`
   *
   * @par Example
   * @snippet table_admin_snippets.cc drop all rows
   */
  Status DropAllRows(std::string const& table_id);

  //@{
  /**
   * @name Snapshot APIs.
   *
   * @warning This is a private alpha release of Cloud Bigtable snapshots. This
   * feature is not currently available to most Cloud Bigtable customers. This
   * feature might be changed in backward-incompatible ways and is not
   * recommended for production use. It is not subject to any SLA or deprecation
   * policy.
   */
  /**
   * Create a new snapshot in the specified cluster from the specified
   * source table.
   *
   * @warning This is a private alpha release of Cloud Bigtable snapshots. This
   * feature is not currently available to most Cloud Bigtable customers. This
   * feature might be changed in backward-incompatible ways and is not
   * recommended for production use. It is not subject to any SLA or deprecation
   * policy.
   *
   * @param cluster_id the cluster id to which snapshot is created.
   * @param snapshot_id the id of the snapshot.
   * @param table_id the id of the table for which snapshot is created.
   * @param duration_ttl time to live for snapshot being created.
   * @return a future that becomes satisfied when (a) the operation has
   *   completed successfully, in which case it returns a proto with the
   *   Snapshot details, (b) the operation has failed, in which case the future
   *   contains an exception (typically `bigtable::GrpcError`) with the details
   *   of the failure, or (c) the state of the operation is unknown after the
   *   time allocated by the retry policies has expired, in which case the
   *   future contains an exception of type `bigtable::PollTimeout`.
   *
   */
  std::future<StatusOr<google::bigtable::admin::v2::Snapshot>> SnapshotTable(
      bigtable::ClusterId const& cluster_id,
      bigtable::SnapshotId const& snapshot_id,
      bigtable::TableId const& table_id, std::chrono::seconds duration_ttl);

  /**
   * Get information about a single snapshot.
   *
   * @warning This is a private alpha release of Cloud Bigtable snapshots. This
   * feature is not currently available to most Cloud Bigtable customers. This
   * feature might be changed in backward-incompatible ways and is not
   * recommended for production use. It is not subject to any SLA or deprecation
   * policy.
   *
   * @param cluster_id the cluster id to which snapshot is associated.
   * @param snapshot_id the id of the snapshot.
   * @return the information about the snapshot.
   *
   * @par Example
   * @snippet table_admin_snippets.cc get snapshot
   */
  StatusOr<google::bigtable::admin::v2::Snapshot> GetSnapshot(
      bigtable::ClusterId const& cluster_id,
      bigtable::SnapshotId const& snapshot_id);

  /**
   * Delete a snapshot.
   *
   * @warning This is a private alpha release of Cloud Bigtable snapshots. This
   * feature is not currently available to most Cloud Bigtable customers. This
   * feature might be changed in backward-incompatible ways and is not
   * recommended for production use. It is not subject to any SLA or deprecation
   * policy.
   *
   * @param cluster_id the id of the cluster to which snapshot belongs.
   * @param snapshot_id the id of the snapshot which needs to be deleted.
   *
   * @par Example
   * @snippet table_admin_snippets.cc delete snapshot
   */
  Status DeleteSnapshot(bigtable::ClusterId const& cluster_id,
                        bigtable::SnapshotId const& snapshot_id);

  /**
   * Create table from snapshot.
   *
   * @warning This is a private alpha release of Cloud Bigtable snapshots. This
   * feature is not currently available to most Cloud Bigtable customers. This
   * feature might be changed in backward-incompatible ways and is not
   * recommended for production use. It is not subject to any SLA or deprecation
   * policy.
   *
   * @param cluster_id the id of the cluster to which snapshot belongs.
   * @param snapshot_id the id of the snapshot to which table belongs.
   * @param table_id the id of the table which needs to be created.
   * @throws std::exception if the operation cannot be completed.
   *
   * @par Example
   * @snippet table_admin_snippets.cc create table from snapshot
   */
  std::future<StatusOr<google::bigtable::admin::v2::Table>>
  CreateTableFromSnapshot(bigtable::ClusterId const& cluster_id,
                          bigtable::SnapshotId const& snapshot_id,
                          std::string table_id);

  /**
   * List snapshots in the given instance.
   *
   * @warning This is a private alpha release of Cloud Bigtable snapshots. This
   * feature is not currently available to most Cloud Bigtable customers. This
   * feature might be changed in backward-incompatible ways and is not
   * recommended for production use. It is not subject to any SLA or deprecation
   * policy.
   *
   * @param cluster_id the name of the cluster for which snapshots should be
   * listed.
   * @return vector containing the snapshots for the given cluster.
   *
   * @par Example
   * @snippet table_admin_snippets.cc list snapshots
   */
  StatusOr<std::vector<::google::bigtable::admin::v2::Snapshot>> ListSnapshots(
      bigtable::ClusterId const& cluster_id = bigtable::ClusterId("-"));
  //@}

  /// Return the fully qualified name of a table in this object's instance.
  std::string TableName(std::string const& table_id) const {
    return instance_name() + "/tables/" + table_id;
  }

  /// Return the fully qualified name of a snapshot.
  std::string SnapshotName(bigtable::ClusterId const& cluster_id,
                           bigtable::SnapshotId const& snapshot_id) {
    return instance_name() + "/clusters/" + cluster_id.get() + "/snapshots/" +
           snapshot_id.get();
  }

  /// Return the fully qualified name of a Cluster.
  std::string ClusterName(bigtable::ClusterId const& cluster_id) {
    return instance_name() + "/clusters/" + cluster_id.get();
  }

 private:
  /**
   * Implements the polling loop for `WaitForConsistencyCheck` on a
   * separate thread
   */
  StatusOr<bool> WaitForConsistencyCheckImpl(
      bigtable::TableId const& table_id,
      bigtable::ConsistencyToken const& consistency_token);

  /**
   * Implements the polling loop for `SnapshotTable` in a
   * separate thread
   */
  StatusOr<google::bigtable::admin::v2::Snapshot> SnapshotTableImpl(
      bigtable::ClusterId const& cluster_id,
      bigtable::SnapshotId const& snapshot_id,
      bigtable::TableId const& table_id, std::chrono::seconds duration_ttl);

  /// Implement CreateTableFromSnapshot() with a separate thread.
  StatusOr<google::bigtable::admin::v2::Table> CreateTableFromSnapshotImpl(
      bigtable::ClusterId const& cluster_id,
      bigtable::SnapshotId const& snapshot_id, std::string table_id);

 private:
  std::unique_ptr<RPCRetryPolicy> clone_rpc_retry_policy() {
    return impl_.rpc_retry_policy_->clone();
  }

  std::unique_ptr<RPCBackoffPolicy> clone_rpc_backoff_policy() {
    return impl_.rpc_backoff_policy_->clone();
  }

  MetadataUpdatePolicy clone_metadata_update_policy() {
    return impl_.metadata_update_policy_;
  }

  std::unique_ptr<PollingPolicy> clone_polling_policy() {
    return impl_.polling_policy_->clone();
  }

  noex::TableAdmin impl_;
};

}  // namespace BIGTABLE_CLIENT_NS
}  // namespace bigtable
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_TABLE_ADMIN_H_
