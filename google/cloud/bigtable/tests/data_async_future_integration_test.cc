// Copyright 2019 Google LLC
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

#include "google/cloud/bigtable/testing/table_integration_test.h"
#include "google/cloud/testing_util/assert_ok.h"
#include "google/cloud/testing_util/chrono_literals.h"
#include "google/cloud/testing_util/init_google_mock.h"

namespace google {
namespace cloud {
namespace bigtable {
inline namespace BIGTABLE_CLIENT_NS {
namespace {
class DataAsyncFutureIntegrationTest
    : public bigtable::testing::TableIntegrationTest {
 protected:
  std::string const family = "family1";
};

using namespace google::cloud::testing_util::chrono_literals;

TEST_F(DataAsyncFutureIntegrationTest, TableAsyncApply) {
  auto table = GetTable();

  std::string const row_key = "key-000010";
  std::vector<bigtable::Cell> created{{row_key, family, "cc1", 1000, "v1000"},
                                      {row_key, family, "cc2", 2000, "v2000"}};
  SingleRowMutation mut(row_key);
  for (auto const& c : created) {
    mut.emplace_back(SetCell(
        c.family_name(), c.column_qualifier(),
        std::chrono::duration_cast<std::chrono::milliseconds>(c.timestamp()),
        c.value()));
  }

  CompletionQueue cq;
  std::thread pool([&cq] { cq.Run(); });

  auto fut = table.AsyncApply(std::move(mut), cq);

  // Block until the asynchronous operation completes. This is not what one
  // would do in a real application (the synchronous API is better in that
  // case), but we need to wait before checking the results.
  Status status = fut.get();
  EXPECT_STATUS_OK(status);
  EXPECT_TRUE(status.ok());

  // Validate that the newly created cells are actually in the server.
  std::vector<bigtable::Cell> expected{{row_key, family, "cc1", 1000, "v1000"},
                                       {row_key, family, "cc2", 2000, "v2000"}};

  auto actual = ReadRows(table, bigtable::Filter::PassAllFilter());

  // Cleanup the thread running the completion queue event loop.
  cq.Shutdown();
  pool.join();
  CheckEqualUnordered(expected, actual);
}

TEST_F(DataAsyncFutureIntegrationTest, TableAsyncBulkApply) {
  auto table = GetTable();

  std::string const row_key1 = "key-000010";
  std::string const row_key2 = "key-000020";
  std::map<std::string, std::vector<bigtable::Cell>> created{
      {row_key1,
       {{row_key1, family, "cc1", 1000, "vv10"},
        {row_key1, family, "cc2", 2000, "vv20"}}},
      {row_key2,
       {{row_key2, family, "cc1", 3000, "vv30"},
        {row_key2, family, "cc2", 4000, "vv40"}}}};

  BulkMutation mut;
  for (auto const& row_cells : created) {
    auto const& row_key = row_cells.first;
    auto const& cells = row_cells.second;
    SingleRowMutation row_mut(row_key);
    for (auto const& c : cells) {
      row_mut.emplace_back(SetCell(
          c.family_name(), c.column_qualifier(),
          std::chrono::duration_cast<std::chrono::milliseconds>(c.timestamp()),
          c.value()));
    }
    mut.push_back(row_mut);
  }

  CompletionQueue cq;
  std::thread pool([&cq] { cq.Run(); });

  auto fut_void = table.AsyncBulkApply(std::move(mut), cq);

  // Block until the asynchronous operation completes. This is not what one
  // would do in a real application (the synchronous API is better in that
  // case), but we need to wait before checking the results.
  fut_void.get();

  // Validate that the newly created cells are actually in the server.
  std::vector<bigtable::Cell> expected;
  for (auto const& row_cells : created) {
    auto const& cells = row_cells.second;
    for (auto const& c : cells) {
      expected.push_back(c);
    }
  }

  auto actual = ReadRows(table, bigtable::Filter::PassAllFilter());

  // Cleanup the thread running the completion queue event loop.
  cq.Shutdown();
  pool.join();
  CheckEqualUnordered(expected, actual);
}

TEST_F(DataAsyncFutureIntegrationTest, TableAsyncCheckAndMutateRowPass) {
  auto table = GetTable();

  std::string const key = "row-key";

  std::vector<bigtable::Cell> created{{key, family, "c1", 0, "v1000"}};
  CreateCells(table, created);

  CompletionQueue cq;
  std::thread pool([&cq] { cq.Run(); });

  auto fut = table.AsyncCheckAndMutateRow(
      key, bigtable::Filter::ValueRegex("v1000"),
      {bigtable::SetCell(family, "c2", 0_ms, "v2000")},
      {bigtable::SetCell(family, "c3", 0_ms, "v3000")}, cq);

  // Block until the asynchronous operation completes. This is not what one
  // would do in a real application (the synchronous API is better in that
  // case), but we need to wait before checking the results.
  auto status = fut.get();
  EXPECT_STATUS_OK(status);
  EXPECT_TRUE(status.ok());

  std::vector<bigtable::Cell> expected{{key, family, "c1", 0, "v1000"},
                                       {key, family, "c2", 0, "v2000"}};

  auto actual = ReadRows(table, bigtable::Filter::PassAllFilter());

  // Cleanup the thread running the completion queue event loop.
  cq.Shutdown();
  pool.join();
  CheckEqualUnordered(expected, actual);
}

TEST_F(DataAsyncFutureIntegrationTest, TableAsyncCheckAndMutateRowFail) {
  auto table = GetTable();

  std::string const key = "row-key";

  std::vector<bigtable::Cell> created{{key, family, "c1", 0, "v1000"}};
  CreateCells(table, created);

  CompletionQueue cq;
  std::thread pool([&cq] { cq.Run(); });

  auto fut = table.AsyncCheckAndMutateRow(
      key, bigtable::Filter::ValueRegex("not-there"),
      {bigtable::SetCell(family, "c2", 0_ms, "v2000")},
      {bigtable::SetCell(family, "c3", 0_ms, "v3000")}, cq);

  // Block until the asynchronous operation completes. This is not what one
  // would do in a real application (the synchronous API is better in that
  // case), but we need to wait before checking the results.
  auto status = fut.get();
  EXPECT_STATUS_OK(status);
  EXPECT_TRUE(status.ok());

  std::vector<bigtable::Cell> expected{{key, family, "c1", 0, "v1000"},
                                       {key, family, "c3", 0, "v3000"}};

  auto actual = ReadRows(table, bigtable::Filter::PassAllFilter());

  // Cleanup the thread running the completion queue event loop.
  cq.Shutdown();
  pool.join();
  CheckEqualUnordered(expected, actual);
}

TEST_F(DataAsyncFutureIntegrationTest,
       TableAsyncReadModifyWriteAppendValueTest) {
  auto table = GetTable();
  std::string const row_key1 = "row-key-1";
  std::string const row_key2 = "row-key-2";
  std::string const add_suffix1 = "-suffix";
  std::string const add_suffix2 = "-next";
  std::string const add_suffix3 = "-newrecord";

  std::string const family1 = "family1";
  std::string const family2 = "family2";
  std::string const family3 = "family3";
  std::string const family4 = "family4";

  std::vector<bigtable::Cell> created{
      {row_key1, family1, "column-id1", 1000, "v1000"},
      {row_key1, family2, "column-id2", 2000, "v2000"}};

  std::vector<bigtable::Cell> expected{
      {row_key1, family1, "column-id1", 1000, "v1000"},
      {row_key1, family2, "column-id2", 2000, "v2000"},
      {row_key1, family1, "column-id1", 1000, "v1000" + add_suffix1},
      {row_key1, family2, "column-id2", 2000, "v2000" + add_suffix2},
      {row_key1, family3, "column-id3", 2000, add_suffix3}};

  CreateCells(table, created);
  using R = bigtable::ReadModifyWriteRule;

  CompletionQueue cq;
  std::thread pool([&cq] { cq.Run(); });

  auto fut = table.AsyncReadModifyWriteRow(
      row_key1, cq, R::AppendValue(family1, "column-id1", add_suffix1),
      R::AppendValue(family2, "column-id2", add_suffix2),
      R::AppendValue(family3, "column-id3", add_suffix3));

  // Block until the asynchronous operation completes. This is not what one
  // would do in a real application (the synchronous API is better in that
  // case), but we need to wait before checking the results.
  auto status = fut.get();
  EXPECT_STATUS_OK(status);
  EXPECT_TRUE(status.ok());

  auto actual = ReadRows(table, bigtable::Filter::PassAllFilter());
  // Creating cells by ignoring the timestamps
  // The returned cells have the timestamps in microseconds and do not match
  // with the ones in the expected cells.
  auto actual_cells_ignore_timestamp = GetCellsIgnoringTimestamp(actual);
  auto expected_cells_ignore_timestamp = GetCellsIgnoringTimestamp(expected);

  // Cleanup the thread running the completion queue event loop.
  cq.Shutdown();
  pool.join();
  CheckEqualUnordered(expected_cells_ignore_timestamp,
                      actual_cells_ignore_timestamp);
}
}  // namespace
}  // namespace BIGTABLE_CLIENT_NS
}  // namespace bigtable
}  // namespace cloud
}  // namespace google

int main(int argc, char* argv[]) {
  google::cloud::testing_util::InitGoogleMock(argc, argv);

  // Make sure the arguments are valid.
  if (argc != 3) {
    std::string const cmd = argv[0];
    auto last_slash = std::string(argv[0]).find_last_of('/');
    std::cerr << "Usage: " << cmd.substr(last_slash + 1)
              << " <project> <instance>\n";
    return 1;
  }

  std::string const project_id = argv[1];
  std::string const instance_id = argv[2];

  (void)::testing::AddGlobalTestEnvironment(
      new google::cloud::bigtable::testing::TableTestEnvironment(project_id,
                                                                 instance_id));

  return RUN_ALL_TESTS();
}
