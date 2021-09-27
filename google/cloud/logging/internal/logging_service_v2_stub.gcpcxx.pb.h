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
// source: google/logging/v2/logging.proto
#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LOGGING_INTERNAL_LOGGING_SERVICE_V2_STUB_GCPCXX_PB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LOGGING_INTERNAL_LOGGING_SERVICE_V2_STUB_GCPCXX_PB_H

#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/logging/v2/logging.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
inline namespace GOOGLE_CLOUD_CPP_NS {
namespace logging_internal {

class LoggingServiceV2Stub {
 public:
  virtual ~LoggingServiceV2Stub() = 0;

  virtual Status DeleteLog(
      grpc::ClientContext& context,
      ::google::logging::v2::DeleteLogRequest const& request) = 0;

  virtual StatusOr<::google::logging::v2::WriteLogEntriesResponse>
  WriteLogEntries(
      grpc::ClientContext& context,
      ::google::logging::v2::WriteLogEntriesRequest const& request) = 0;

  virtual StatusOr<::google::logging::v2::ListLogEntriesResponse>
  ListLogEntries(
      grpc::ClientContext& context,
      ::google::logging::v2::ListLogEntriesRequest const& request) = 0;

  virtual StatusOr<
      ::google::logging::v2::ListMonitoredResourceDescriptorsResponse>
  ListMonitoredResourceDescriptors(
      grpc::ClientContext& context,
      ::google::logging::v2::ListMonitoredResourceDescriptorsRequest const&
          request) = 0;

  virtual StatusOr<::google::logging::v2::ListLogsResponse> ListLogs(
      grpc::ClientContext& context,
      ::google::logging::v2::ListLogsRequest const& request) = 0;
};

class DefaultLoggingServiceV2Stub : public LoggingServiceV2Stub {
 public:
  explicit DefaultLoggingServiceV2Stub(
      std::unique_ptr<::google::logging::v2::LoggingServiceV2::StubInterface>
          grpc_stub)
      : grpc_stub_(std::move(grpc_stub)) {}

  Status DeleteLog(
      grpc::ClientContext& client_context,
      ::google::logging::v2::DeleteLogRequest const& request) override;

  StatusOr<::google::logging::v2::WriteLogEntriesResponse> WriteLogEntries(
      grpc::ClientContext& client_context,
      ::google::logging::v2::WriteLogEntriesRequest const& request) override;

  StatusOr<::google::logging::v2::ListLogEntriesResponse> ListLogEntries(
      grpc::ClientContext& client_context,
      ::google::logging::v2::ListLogEntriesRequest const& request) override;

  StatusOr<::google::logging::v2::ListMonitoredResourceDescriptorsResponse>
  ListMonitoredResourceDescriptors(
      grpc::ClientContext& client_context,
      ::google::logging::v2::ListMonitoredResourceDescriptorsRequest const&
          request) override;

  StatusOr<::google::logging::v2::ListLogsResponse> ListLogs(
      grpc::ClientContext& client_context,
      ::google::logging::v2::ListLogsRequest const& request) override;

 private:
  std::unique_ptr<::google::logging::v2::LoggingServiceV2::StubInterface>
      grpc_stub_;
};

}  // namespace logging_internal
}  // namespace GOOGLE_CLOUD_CPP_NS
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_LOGGING_INTERNAL_LOGGING_SERVICE_V2_STUB_GCPCXX_PB_H
