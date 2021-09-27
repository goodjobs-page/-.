// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_EXAMPLES_BIGTABLE_EXAMPLES_COMMON_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_EXAMPLES_BIGTABLE_EXAMPLES_COMMON_H

#include "google/cloud/bigtable/table_admin.h"
#include "google/cloud/internal/random.h"
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace google {
namespace cloud {
namespace bigtable {
namespace examples {

// TODO(#3624) - refactor this class to -common
class Usage : public std::runtime_error {
 public:
  explicit Usage(std::string const& msg) : std::runtime_error(msg) {}
};

// TODO(#3624) - refactor these types to -common
using CommandType = std::function<void(std::vector<std::string> const& argv)>;
using Commands = std::map<std::string, CommandType>;

// TODO(#3624) - refactor this class to -common
class Example {
 public:
  explicit Example(std::map<std::string, CommandType> commands);

  int Run(int argc, char const* const argv[]);

 private:
  void PrintUsage(std::string const& cmd, std::string const& msg);

  std::map<std::string, CommandType> commands_;
  std::string full_usage_;
};

std::string TablePrefix(std::string const& prefix,
                        std::chrono::system_clock::time_point tp);
std::string RandomTableId(std::string const& prefix,
                          google::cloud::internal::DefaultPRNG& generator);
void CleanupOldTables(std::string const& prefix,
                      google::cloud::bigtable::TableAdmin admin);
bool UsingEmulator();
bool RunAdminIntegrationTests();
void CheckEnvironmentVariablesAreSet(std::vector<std::string> const&);

}  // namespace examples
}  // namespace bigtable
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_EXAMPLES_BIGTABLE_EXAMPLES_COMMON_H
