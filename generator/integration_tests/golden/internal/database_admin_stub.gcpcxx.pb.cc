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
// source: generator/integration_tests/test.proto

#include "generator/integration_tests/golden/internal/database_admin_stub.gcpcxx.pb.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/status_or.h"
#include <generator/integration_tests/test.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
inline namespace GOOGLE_CLOUD_CPP_NS {
namespace golden_internal {

DatabaseAdminStub::~DatabaseAdminStub() = default;

StatusOr<::google::test::admin::database::v1::ListDatabasesResponse>
DefaultDatabaseAdminStub::ListDatabases(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::ListDatabasesRequest const& request) {
    ::google::test::admin::database::v1::ListDatabasesResponse response;
    auto status =
        grpc_stub_->ListDatabases(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::longrunning::Operation>
DefaultDatabaseAdminStub::CreateDatabase(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::CreateDatabaseRequest const& request) {
    ::google::longrunning::Operation response;
    auto status =
        grpc_stub_->CreateDatabase(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::test::admin::database::v1::Database>
DefaultDatabaseAdminStub::GetDatabase(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::GetDatabaseRequest const& request) {
    ::google::test::admin::database::v1::Database response;
    auto status =
        grpc_stub_->GetDatabase(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::longrunning::Operation>
DefaultDatabaseAdminStub::UpdateDatabaseDdl(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::UpdateDatabaseDdlRequest const& request) {
    ::google::longrunning::Operation response;
    auto status =
        grpc_stub_->UpdateDatabaseDdl(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

Status
DefaultDatabaseAdminStub::DropDatabase(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::DropDatabaseRequest const& request) {
    ::google::protobuf::Empty response;
    auto status =
        grpc_stub_->DropDatabase(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return google::cloud::Status();
}

StatusOr<::google::test::admin::database::v1::GetDatabaseDdlResponse>
DefaultDatabaseAdminStub::GetDatabaseDdl(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::GetDatabaseDdlRequest const& request) {
    ::google::test::admin::database::v1::GetDatabaseDdlResponse response;
    auto status =
        grpc_stub_->GetDatabaseDdl(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::iam::v1::Policy>
DefaultDatabaseAdminStub::SetIamPolicy(
  grpc::ClientContext& client_context,
  ::google::iam::v1::SetIamPolicyRequest const& request) {
    ::google::iam::v1::Policy response;
    auto status =
        grpc_stub_->SetIamPolicy(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::iam::v1::Policy>
DefaultDatabaseAdminStub::GetIamPolicy(
  grpc::ClientContext& client_context,
  ::google::iam::v1::GetIamPolicyRequest const& request) {
    ::google::iam::v1::Policy response;
    auto status =
        grpc_stub_->GetIamPolicy(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::iam::v1::TestIamPermissionsResponse>
DefaultDatabaseAdminStub::TestIamPermissions(
  grpc::ClientContext& client_context,
  ::google::iam::v1::TestIamPermissionsRequest const& request) {
    ::google::iam::v1::TestIamPermissionsResponse response;
    auto status =
        grpc_stub_->TestIamPermissions(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::longrunning::Operation>
DefaultDatabaseAdminStub::CreateBackup(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::CreateBackupRequest const& request) {
    ::google::longrunning::Operation response;
    auto status =
        grpc_stub_->CreateBackup(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::test::admin::database::v1::Backup>
DefaultDatabaseAdminStub::GetBackup(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::GetBackupRequest const& request) {
    ::google::test::admin::database::v1::Backup response;
    auto status =
        grpc_stub_->GetBackup(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::test::admin::database::v1::Backup>
DefaultDatabaseAdminStub::UpdateBackup(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::UpdateBackupRequest const& request) {
    ::google::test::admin::database::v1::Backup response;
    auto status =
        grpc_stub_->UpdateBackup(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

Status
DefaultDatabaseAdminStub::DeleteBackup(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::DeleteBackupRequest const& request) {
    ::google::protobuf::Empty response;
    auto status =
        grpc_stub_->DeleteBackup(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return google::cloud::Status();
}

StatusOr<::google::test::admin::database::v1::ListBackupsResponse>
DefaultDatabaseAdminStub::ListBackups(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::ListBackupsRequest const& request) {
    ::google::test::admin::database::v1::ListBackupsResponse response;
    auto status =
        grpc_stub_->ListBackups(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::longrunning::Operation>
DefaultDatabaseAdminStub::RestoreDatabase(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::RestoreDatabaseRequest const& request) {
    ::google::longrunning::Operation response;
    auto status =
        grpc_stub_->RestoreDatabase(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::test::admin::database::v1::ListDatabaseOperationsResponse>
DefaultDatabaseAdminStub::ListDatabaseOperations(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::ListDatabaseOperationsRequest const& request) {
    ::google::test::admin::database::v1::ListDatabaseOperationsResponse response;
    auto status =
        grpc_stub_->ListDatabaseOperations(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

StatusOr<::google::test::admin::database::v1::ListBackupOperationsResponse>
DefaultDatabaseAdminStub::ListBackupOperations(
  grpc::ClientContext& client_context,
  ::google::test::admin::database::v1::ListBackupOperationsRequest const& request) {
    ::google::test::admin::database::v1::ListBackupOperationsResponse response;
    auto status =
        grpc_stub_->ListBackupOperations(&client_context, request, &response);
    if (!status.ok()) {
      return google::cloud::MakeStatusFromRpcError(status);
    }
    return response;
}

/// Poll a long-running operation.
StatusOr<google::longrunning::Operation>
DefaultDatabaseAdminStub::GetOperation(
    grpc::ClientContext& client_context,
    google::longrunning::GetOperationRequest const& request) {
  google::longrunning::Operation response;
  grpc::Status status =
      operations_->GetOperation(&client_context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}
/// Cancel a long-running operation.
Status DefaultDatabaseAdminStub::CancelOperation(
    grpc::ClientContext& client_context,
    google::longrunning::CancelOperationRequest const& request) {
  google::protobuf::Empty response;
  grpc::Status status =
      operations_->CancelOperation(&client_context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}
}  // namespace golden_internal
}  // namespace GOOGLE_CLOUD_CPP_NS
}  // namespace cloud
}  // namespace google

