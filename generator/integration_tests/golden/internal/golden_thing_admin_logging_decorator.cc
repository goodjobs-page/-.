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
#include "generator/integration_tests/golden/internal/golden_thing_admin_logging_decorator.h"
#include "google/cloud/internal/log_wrapper.h"
#include "google/cloud/status_or.h"
#include <generator/integration_tests/test.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace golden_internal {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

GoldenThingAdminLogging::GoldenThingAdminLogging(
    std::shared_ptr<GoldenThingAdminStub> child,
    TracingOptions tracing_options,
    std::set<std::string> components)
    : child_(std::move(child)), tracing_options_(std::move(tracing_options)),
      components_(std::move(components)) {}

StatusOr<::google::test::admin::database::v1::ListDatabasesResponse>
GoldenThingAdminLogging::ListDatabases(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::ListDatabasesRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::ListDatabasesRequest const& request) {
        return child_->ListDatabases(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::longrunning::Operation>
GoldenThingAdminLogging::CreateDatabase(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::CreateDatabaseRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::CreateDatabaseRequest const& request) {
        return child_->CreateDatabase(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::Database>
GoldenThingAdminLogging::GetDatabase(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::GetDatabaseRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::GetDatabaseRequest const& request) {
        return child_->GetDatabase(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::longrunning::Operation>
GoldenThingAdminLogging::UpdateDatabaseDdl(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::UpdateDatabaseDdlRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::UpdateDatabaseDdlRequest const& request) {
        return child_->UpdateDatabaseDdl(context, request);
      },
      context, request, __func__, tracing_options_);
}

Status
GoldenThingAdminLogging::DropDatabase(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::DropDatabaseRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::DropDatabaseRequest const& request) {
        return child_->DropDatabase(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::GetDatabaseDdlResponse>
GoldenThingAdminLogging::GetDatabaseDdl(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::GetDatabaseDdlRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::GetDatabaseDdlRequest const& request) {
        return child_->GetDatabaseDdl(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::iam::v1::Policy>
GoldenThingAdminLogging::SetIamPolicy(
    grpc::ClientContext& context,
    ::google::iam::v1::SetIamPolicyRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::iam::v1::SetIamPolicyRequest const& request) {
        return child_->SetIamPolicy(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::iam::v1::Policy>
GoldenThingAdminLogging::GetIamPolicy(
    grpc::ClientContext& context,
    ::google::iam::v1::GetIamPolicyRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::iam::v1::GetIamPolicyRequest const& request) {
        return child_->GetIamPolicy(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::iam::v1::TestIamPermissionsResponse>
GoldenThingAdminLogging::TestIamPermissions(
    grpc::ClientContext& context,
    ::google::iam::v1::TestIamPermissionsRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::iam::v1::TestIamPermissionsRequest const& request) {
        return child_->TestIamPermissions(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::longrunning::Operation>
GoldenThingAdminLogging::CreateBackup(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::CreateBackupRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::CreateBackupRequest const& request) {
        return child_->CreateBackup(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::Backup>
GoldenThingAdminLogging::GetBackup(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::GetBackupRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::GetBackupRequest const& request) {
        return child_->GetBackup(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::Backup>
GoldenThingAdminLogging::UpdateBackup(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::UpdateBackupRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::UpdateBackupRequest const& request) {
        return child_->UpdateBackup(context, request);
      },
      context, request, __func__, tracing_options_);
}

Status
GoldenThingAdminLogging::DeleteBackup(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::DeleteBackupRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::DeleteBackupRequest const& request) {
        return child_->DeleteBackup(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::ListBackupsResponse>
GoldenThingAdminLogging::ListBackups(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::ListBackupsRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::ListBackupsRequest const& request) {
        return child_->ListBackups(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::longrunning::Operation>
GoldenThingAdminLogging::RestoreDatabase(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::RestoreDatabaseRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::RestoreDatabaseRequest const& request) {
        return child_->RestoreDatabase(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::ListDatabaseOperationsResponse>
GoldenThingAdminLogging::ListDatabaseOperations(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::ListDatabaseOperationsRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::ListDatabaseOperationsRequest const& request) {
        return child_->ListDatabaseOperations(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<::google::test::admin::database::v1::ListBackupOperationsResponse>
GoldenThingAdminLogging::ListBackupOperations(
    grpc::ClientContext& context,
    ::google::test::admin::database::v1::ListBackupOperationsRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             ::google::test::admin::database::v1::ListBackupOperationsRequest const& request) {
        return child_->ListBackupOperations(context, request);
      },
      context, request, __func__, tracing_options_);
}

StatusOr<google::longrunning::Operation> GoldenThingAdminLogging::GetOperation(
    grpc::ClientContext& context,
    google::longrunning::GetOperationRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::longrunning::GetOperationRequest const& request) {
        return child_->GetOperation(context, request);
      },
      context, request, __func__, tracing_options_);
}

Status GoldenThingAdminLogging::CancelOperation(
    grpc::ClientContext& context,
    google::longrunning::CancelOperationRequest const& request) {
  return google::cloud::internal::LogWrapper(
      [this](grpc::ClientContext& context,
             google::longrunning::CancelOperationRequest const& request) {
        return child_->CancelOperation(context, request);
      },
      context, request, __func__, tracing_options_);
}
}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace golden_internal
}  // namespace cloud
}  // namespace google

