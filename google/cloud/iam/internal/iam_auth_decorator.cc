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
// source: google/iam/admin/v1/iam.proto

#include "google/cloud/iam/internal/iam_auth_decorator.h"
#include <google/iam/admin/v1/iam.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace iam_internal {
inline namespace GOOGLE_CLOUD_CPP_GENERATED_NS {

IAMAuth::IAMAuth(
    std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
    std::shared_ptr<IAMStub> child)
    : auth_(std::move(auth)), child_(std::move(child)) {}

StatusOr<google::iam::admin::v1::ListServiceAccountsResponse>
IAMAuth::ListServiceAccounts(
    grpc::ClientContext& context,
    google::iam::admin::v1::ListServiceAccountsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListServiceAccounts(context, request);
}

StatusOr<google::iam::admin::v1::ServiceAccount> IAMAuth::GetServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::GetServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetServiceAccount(context, request);
}

StatusOr<google::iam::admin::v1::ServiceAccount> IAMAuth::CreateServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::CreateServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateServiceAccount(context, request);
}

StatusOr<google::iam::admin::v1::ServiceAccount> IAMAuth::PatchServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::PatchServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->PatchServiceAccount(context, request);
}

Status IAMAuth::DeleteServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::DeleteServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteServiceAccount(context, request);
}

StatusOr<google::iam::admin::v1::UndeleteServiceAccountResponse>
IAMAuth::UndeleteServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::UndeleteServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UndeleteServiceAccount(context, request);
}

Status IAMAuth::EnableServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::EnableServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->EnableServiceAccount(context, request);
}

Status IAMAuth::DisableServiceAccount(
    grpc::ClientContext& context,
    google::iam::admin::v1::DisableServiceAccountRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DisableServiceAccount(context, request);
}

StatusOr<google::iam::admin::v1::ListServiceAccountKeysResponse>
IAMAuth::ListServiceAccountKeys(
    grpc::ClientContext& context,
    google::iam::admin::v1::ListServiceAccountKeysRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListServiceAccountKeys(context, request);
}

StatusOr<google::iam::admin::v1::ServiceAccountKey>
IAMAuth::GetServiceAccountKey(
    grpc::ClientContext& context,
    google::iam::admin::v1::GetServiceAccountKeyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetServiceAccountKey(context, request);
}

StatusOr<google::iam::admin::v1::ServiceAccountKey>
IAMAuth::CreateServiceAccountKey(
    grpc::ClientContext& context,
    google::iam::admin::v1::CreateServiceAccountKeyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateServiceAccountKey(context, request);
}

StatusOr<google::iam::admin::v1::ServiceAccountKey>
IAMAuth::UploadServiceAccountKey(
    grpc::ClientContext& context,
    google::iam::admin::v1::UploadServiceAccountKeyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UploadServiceAccountKey(context, request);
}

Status IAMAuth::DeleteServiceAccountKey(
    grpc::ClientContext& context,
    google::iam::admin::v1::DeleteServiceAccountKeyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteServiceAccountKey(context, request);
}

StatusOr<google::iam::v1::Policy> IAMAuth::GetIamPolicy(
    grpc::ClientContext& context,
    google::iam::v1::GetIamPolicyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetIamPolicy(context, request);
}

StatusOr<google::iam::v1::Policy> IAMAuth::SetIamPolicy(
    grpc::ClientContext& context,
    google::iam::v1::SetIamPolicyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->SetIamPolicy(context, request);
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
IAMAuth::TestIamPermissions(
    grpc::ClientContext& context,
    google::iam::v1::TestIamPermissionsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->TestIamPermissions(context, request);
}

StatusOr<google::iam::admin::v1::QueryGrantableRolesResponse>
IAMAuth::QueryGrantableRoles(
    grpc::ClientContext& context,
    google::iam::admin::v1::QueryGrantableRolesRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->QueryGrantableRoles(context, request);
}

StatusOr<google::iam::admin::v1::ListRolesResponse> IAMAuth::ListRoles(
    grpc::ClientContext& context,
    google::iam::admin::v1::ListRolesRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->ListRoles(context, request);
}

StatusOr<google::iam::admin::v1::Role> IAMAuth::GetRole(
    grpc::ClientContext& context,
    google::iam::admin::v1::GetRoleRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->GetRole(context, request);
}

StatusOr<google::iam::admin::v1::Role> IAMAuth::CreateRole(
    grpc::ClientContext& context,
    google::iam::admin::v1::CreateRoleRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->CreateRole(context, request);
}

StatusOr<google::iam::admin::v1::Role> IAMAuth::UpdateRole(
    grpc::ClientContext& context,
    google::iam::admin::v1::UpdateRoleRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UpdateRole(context, request);
}

StatusOr<google::iam::admin::v1::Role> IAMAuth::DeleteRole(
    grpc::ClientContext& context,
    google::iam::admin::v1::DeleteRoleRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->DeleteRole(context, request);
}

StatusOr<google::iam::admin::v1::Role> IAMAuth::UndeleteRole(
    grpc::ClientContext& context,
    google::iam::admin::v1::UndeleteRoleRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->UndeleteRole(context, request);
}

StatusOr<google::iam::admin::v1::QueryTestablePermissionsResponse>
IAMAuth::QueryTestablePermissions(
    grpc::ClientContext& context,
    google::iam::admin::v1::QueryTestablePermissionsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->QueryTestablePermissions(context, request);
}

StatusOr<google::iam::admin::v1::QueryAuditableServicesResponse>
IAMAuth::QueryAuditableServices(
    grpc::ClientContext& context,
    google::iam::admin::v1::QueryAuditableServicesRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->QueryAuditableServices(context, request);
}

StatusOr<google::iam::admin::v1::LintPolicyResponse> IAMAuth::LintPolicy(
    grpc::ClientContext& context,
    google::iam::admin::v1::LintPolicyRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->LintPolicy(context, request);
}
}  // namespace GOOGLE_CLOUD_CPP_GENERATED_NS
}  // namespace iam_internal
}  // namespace cloud
}  // namespace google
