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

#include "generator/internal/options_generator.h"
#include "absl/memory/memory.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/descriptor_utils.h"
#include "generator/internal/predicate_utils.h"
#include "generator/internal/printer.h"
#include <google/api/client.pb.h>
#include <google/protobuf/descriptor.h>

namespace google {
namespace cloud {
namespace generator_internal {

OptionsGenerator::OptionsGenerator(
    google::protobuf::ServiceDescriptor const* service_descriptor,
    VarsDictionary service_vars,
    std::map<std::string, VarsDictionary> service_method_vars,
    google::protobuf::compiler::GeneratorContext* context)
    : ServiceCodeGenerator("options_header_path", service_descriptor,
                           std::move(service_vars),
                           std::move(service_method_vars), context) {}

Status OptionsGenerator::GenerateHeader() {
  HeaderPrint(CopyrightLicenseFileHeader());
  HeaderPrint(  // clang-format off
    "// Generated by the Codegen C++ plugin.\n"
    "// If you make any local changes, they will be lost.\n"
    "// source: $proto_file_name$\n"
    "#ifndef $header_include_guard$\n"
    "#define $header_include_guard$\n"
    "\n");
  // clang-format on

  // includes
  HeaderLocalIncludes({vars("connection_header_path"),
                       vars("idempotency_policy_header_path"),
                       "google/cloud/backoff_policy.h",
                       "google/cloud/options.h", "google/cloud/version.h"});
  HeaderSystemIncludes({"memory"});
  HeaderPrint("\n");

  auto result = HeaderOpenNamespaces();
  if (!result.ok()) return result;

  HeaderPrint({// clang-format off
   {"/// Option to use with `google::cloud::Options`.\n"
    "struct $retry_policy_name$Option {\n"
    "  using Type = std::shared_ptr<$retry_policy_name$>;\n"
    "};\n"
    "\n"
    "/// Option to use with `google::cloud::Options`.\n"
    "struct $service_name$BackoffPolicyOption {\n"
    "  using Type = std::shared_ptr<BackoffPolicy>;\n"
    "};\n"
    "\n"},
   {[this]{return HasLongrunningMethod();},
    "/// Option to use with `google::cloud::Options`.\n"
    "struct $service_name$PollingPolicyOption {\n"
    "  using Type = std::shared_ptr<PollingPolicy>;\n"
    "};\n\n", ""},
   {"/// Option to use with `google::cloud::Options`.\n"
    "struct $idempotency_class_name$Option {\n"
    "  using Type = std::shared_ptr<$idempotency_class_name$>;\n"
    "};\n\n"},
   {"using $service_name$PolicyOptionList =\n"
    "    OptionList<$service_name$RetryPolicyOption,\n"
    "               $service_name$BackoffPolicyOption,\n"},
   {[this]{return HasLongrunningMethod();},
    "               $service_name$PollingPolicyOption,\n", ""},
   {"               $idempotency_class_name$Option>;\n\n"}});
               // clang-format on

  HeaderCloseNamespaces();
  // close header guard
  HeaderPrint(  // clang-format off
    "#endif  // $header_include_guard$\n");
  // clang-format on
  return {};
}

Status OptionsGenerator::GenerateCc() { return {}; }

}  // namespace generator_internal
}  // namespace cloud
}  // namespace google
