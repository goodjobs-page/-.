// Copyright 2018 Google LLC
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

//! [all code]

//! [bigtable includes]
#include "google/cloud/bigtable/table.h"
#include "google/cloud/bigtable/table_admin.h"
//! [bigtable includes]
#include <google/protobuf/text_format.h>
#include <deque>
#include <list>
#include <sstream>

namespace {

//! [run table operations]
void RunTableOperations(google::cloud::bigtable::TableAdmin admin,
                        std::string const& table_id) {
  std::cout << "Creating a table:\n";
  auto schema = admin.CreateTable(
      table_id,
      google::cloud::bigtable::TableConfig(
          {{"fam", google::cloud::bigtable::GcRule::MaxNumVersions(10)},
           {"foo",
            google::cloud::bigtable::GcRule::MaxAge(std::chrono::hours(72))}},
          {}));
  std::cout << " Done\n";

  std::cout << "Listing tables:\n";
  auto tables =
      admin.ListTables(google::bigtable::admin::v2::Table::VIEW_UNSPECIFIED);

  if (!tables) {
    throw std::runtime_error(tables.status().message());
  }
  for (auto const& table : *tables) {
    std::cout << table.name() << "\n";
  }

  std::cout << "Get table:\n";
  auto table =
      admin.GetTable(table_id, google::bigtable::admin::v2::Table::FULL);
  if (!table) {
    throw std::runtime_error(table.status().message());
  }
  std::cout << "Table name : " << table->name() << "\n";

  std::cout << "List table families and GC rules:\n";
  for (auto const& family : table->column_families()) {
    std::string const& family_name = family.first;
    std::string gc_rule;
    google::protobuf::TextFormat::PrintToString(family.second.gc_rule(),
                                                &gc_rule);
    std::cout << "Table Families :" << family_name << "\t\t" << gc_rule << "\n";
  }

  std::cout << "Update a column family GC rule:\n";
  auto schema1 = admin.ModifyColumnFamilies(
      table_id,
      {google::cloud::bigtable::ColumnFamilyModification::Drop("foo"),
       google::cloud::bigtable::ColumnFamilyModification::Update(
           "fam", google::cloud::bigtable::GcRule::Union(
                      google::cloud::bigtable::GcRule::MaxNumVersions(5),
                      google::cloud::bigtable::GcRule::MaxAge(
                          std::chrono::hours(24 * 7)))),
       google::cloud::bigtable::ColumnFamilyModification::Create(
           "bar", google::cloud::bigtable::GcRule::Intersection(
                      google::cloud::bigtable::GcRule::MaxNumVersions(3),
                      google::cloud::bigtable::GcRule::MaxAge(
                          std::chrono::hours(72))))});
  if (!schema1) {
    throw std::runtime_error(schema1.status().message());
  }

  std::string formatted;
  google::protobuf::TextFormat::PrintToString(*schema1, &formatted);
  std::cout << "Schema modified to: " << formatted << "\n";

  std::cout << "Deleting table:\n";
  google::cloud::Status status = admin.DeleteTable(table_id);
  if (!status.ok()) {
    throw std::runtime_error(status.message());
  }
  std::cout << " Done\n";
}
//! [run table operations]

// This full example demonstrate various instance operations
void RunFullExample(google::cloud::bigtable::TableAdmin admin,
                    std::string const& table_id) {
  // [START bigtable_create_table]
  std::cout << "Creating a table:\n";
  auto schema = admin.CreateTable(
      table_id,
      google::cloud::bigtable::TableConfig(
          {{"fam", google::cloud::bigtable::GcRule::MaxNumVersions(10)},
           {"foo",
            google::cloud::bigtable::GcRule::MaxAge(std::chrono::hours(72))}},
          {}));
  std::cout << " Done\n";
  // [END bigtable_create_table]

  // [START bigtable_list_table]
  std::cout << "Listing tables:\n";
  auto tables =
      admin.ListTables(google::bigtable::admin::v2::Table::VIEW_UNSPECIFIED);

  if (!tables) {
    throw std::runtime_error(tables.status().message());
  }
  for (auto const& table : *tables) {
    std::cout << table.name() << "\n";
  }
  // [END bigtable_list_table]

  // [START bigtable_get_table]
  std::cout << "Get table:\n";
  auto table =
      admin.GetTable(table_id, google::bigtable::admin::v2::Table::FULL);
  if (!table) {
    throw std::runtime_error(table.status().message());
  }
  std::cout << "Table name : " << table->name() << "\n";
  // [END bigtable_get_table]

  // [START bigtable_table_families]
  for (auto const& family : table->column_families()) {
    std::string const& family_name = family.first;
    std::string gc_rule;
    google::protobuf::TextFormat::PrintToString(family.second.gc_rule(),
                                                &gc_rule);
    std::cout << "Table Families :" << family_name << "\t\t" << gc_rule << "\n";
  }
  // [END bigtable_table_families]

  // [START bigtable_update_column_family]
  std::cout << "Update a column family GC rule:\n";
  auto schema1 = admin.ModifyColumnFamilies(
      table_id,
      {google::cloud::bigtable::ColumnFamilyModification::Drop("foo"),
       google::cloud::bigtable::ColumnFamilyModification::Update(
           "fam", google::cloud::bigtable::GcRule::Union(
                      google::cloud::bigtable::GcRule::MaxNumVersions(5),
                      google::cloud::bigtable::GcRule::MaxAge(
                          std::chrono::hours(24 * 7)))),
       google::cloud::bigtable::ColumnFamilyModification::Create(
           "bar", google::cloud::bigtable::GcRule::Intersection(
                      google::cloud::bigtable::GcRule::MaxNumVersions(3),
                      google::cloud::bigtable::GcRule::MaxAge(
                          std::chrono::hours(72))))});

  if (!schema1) {
    throw std::runtime_error(schema1.status().message());
  }

  std::string formatted;
  google::protobuf::TextFormat::PrintToString(*schema1, &formatted);
  std::cout << "Schema modified to: " << formatted << "\n";
  // [END bigtable_update_column_family]

  // [START bigtable_delete_table]
  std::cout << "Deleting table:\n";
  google::cloud::Status status = admin.DeleteTable(table_id);
  if (!status.ok()) {
    throw std::runtime_error(status.message());
  }
  std::cout << " Done\n";
  // [END bigtable_delete_table]
}

}  // anonymous namespace

int main(int argc, char* argv[]) try {
  auto print_usage = [argv]() {
    std::string const cmd = argv[0];
    auto last_slash = std::string(cmd).find_last_of('/');
    auto program = cmd.substr(last_slash + 1);
    std::cerr << "\nUsage: " << program
              << " <command> <project_id> [arguments]\n\n"
              << "Examples:\n";
    for (auto example : {"run my-project my-instance my-table",
                         "run-full-example my-project my-instance my-table"}) {
      std::cerr << "  " << program << " " << example << "\n";
    }
    std::cerr << std::flush;
  };

  if (argc != 5) {
    print_usage();
    return 1;
  }

  std::string const command = argv[1];
  std::string const project_id = argv[2];
  std::string const instance_id = argv[3];
  std::string const table_id = argv[4];

  // Connect to the Cloud Bigtable admin endpoint.
  //! [connect admin]
  google::cloud::bigtable::TableAdmin admin(
      google::cloud::bigtable::CreateDefaultAdminClient(
          project_id, google::cloud::bigtable::ClientOptions()),
      instance_id);
  //! [connect admin]

  if (command == "run") {
    RunTableOperations(admin, table_id);
  } else if (command == "run-full-example") {
    RunFullExample(admin, table_id);
  } else {
    std::cerr << "Unknown command: " << command << "\n";
    print_usage();
  }

  return 0;
} catch (std::exception const& ex) {
  std::cerr << "Standard C++ exception raised: " << ex.what() << "\n";
  return 1;
}
//! [all code]
