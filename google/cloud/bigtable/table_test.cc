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

#include "google/cloud/bigtable/table.h"
#include "google/cloud/bigtable/testing/mock_async_failing_rpc_factory.h"
#include "google/cloud/bigtable/testing/table_test_fixture.h"
#include "google/cloud/testing_util/mock_completion_queue.h"

namespace bigtable = google::cloud::bigtable;
namespace bt = ::google::bigtable::v2;
using google::cloud::testing_util::MockCompletionQueue;

/// Define types and functions used in the tests.
namespace {
class TableTest : public bigtable::testing::TableTestFixture {};
}  // anonymous namespace

TEST_F(TableTest, ClientProjectId) {
  EXPECT_EQ(kProjectId, client_->project_id());
}

TEST_F(TableTest, ClientInstanceId) {
  EXPECT_EQ(kInstanceId, client_->instance_id());
}

TEST_F(TableTest, StandaloneInstanceName) {
  EXPECT_EQ(kInstanceName, bigtable::InstanceName(client_));
}

TEST_F(TableTest, StandaloneTableName) {
  EXPECT_EQ(kTableName, bigtable::TableName(client_, kTableId));
}

TEST_F(TableTest, TableName) {
  // clang-format: you are drunk, placing this short function in a single line
  // is not nice.
  EXPECT_EQ(kTableName, table_.table_name());
}

TEST_F(TableTest, TableConstructor) {
  std::string const kOtherTableId = "my-table";
  std::string const kOtherTableName =
      bigtable::TableName(client_, kOtherTableId);
  bigtable::Table table(client_, kOtherTableId);
  EXPECT_EQ(kOtherTableName, table.table_name());
}

TEST_F(TableTest, CopyConstructor) {
  bigtable::Table source(client_, "my-table");
  std::string expected = source.table_name();
  bigtable::Table copy(source);
  EXPECT_EQ(expected, copy.table_name());
}

TEST_F(TableTest, MoveConstructor) {
  bigtable::Table source(client_, "my-table");
  std::string expected = source.table_name();
  bigtable::Table copy(std::move(source));
  EXPECT_EQ(expected, copy.table_name());
}

TEST_F(TableTest, CopyAssignment) {
  bigtable::Table source(client_, "my-table");
  std::string expected = source.table_name();
  bigtable::Table dest(client_, "another-table");
  dest = source;
  EXPECT_EQ(expected, dest.table_name());
}

TEST_F(TableTest, MoveAssignment) {
  bigtable::Table source(client_, "my-table");
  std::string expected = source.table_name();
  bigtable::Table dest(client_, "another-table");
  dest = std::move(source);
  EXPECT_EQ(expected, dest.table_name());
}

TEST_F(TableTest, ChangeOnePolicy) {
  bigtable::Table table(client_, "some-table",
                        bigtable::AlwaysRetryMutationPolicy());
  EXPECT_EQ("", table.app_profile_id());
  EXPECT_THAT(table.table_name(), ::testing::HasSubstr("some-table"));
}

TEST_F(TableTest, ChangePolicies) {
  bigtable::Table table(client_, "some-table",
                        bigtable::AlwaysRetryMutationPolicy(),
                        bigtable::LimitedErrorCountRetryPolicy(42));
  EXPECT_EQ("", table.app_profile_id());
  EXPECT_THAT(table.table_name(), ::testing::HasSubstr("some-table"));
}

TEST_F(TableTest, ConstructorWithAppProfileAndPolicies) {
  bigtable::Table table(client_, "test-profile-id", "some-table",
                        bigtable::AlwaysRetryMutationPolicy(),
                        bigtable::LimitedErrorCountRetryPolicy(42));
  EXPECT_EQ("test-profile-id", table.app_profile_id());
  EXPECT_THAT(table.table_name(), ::testing::HasSubstr("some-table"));
}

std::string const kProjectId = "the-project";
std::string const kInstanceId = "the-instance";
std::string const kTableId = "the-table";

class ValidContextMdAsyncTest : public ::testing::Test {
 public:
  ValidContextMdAsyncTest()
      : cq_impl_(new MockCompletionQueue),
        cq_(cq_impl_),
        client_(new bigtable::testing::MockDataClient) {
    EXPECT_CALL(*client_, project_id())
        .WillRepeatedly(::testing::ReturnRef(kProjectId));
    EXPECT_CALL(*client_, instance_id())
        .WillRepeatedly(::testing::ReturnRef(kInstanceId));
    table_ = google::cloud::internal::make_unique<bigtable::Table>(client_,
                                                                   kTableId);
  }

 protected:
  template <typename ResultType>
  void FinishTest(
      google::cloud::future<google::cloud::StatusOr<ResultType>> res_future) {
    EXPECT_EQ(1U, cq_impl_->size());
    cq_impl_->SimulateCompletion(true);
    EXPECT_EQ(0U, cq_impl_->size());
    auto res = res_future.get();
    EXPECT_FALSE(res);
    EXPECT_EQ(google::cloud::StatusCode::kPermissionDenied,
              res.status().code());
  }

  void FinishTest(google::cloud::future<google::cloud::Status> res_future) {
    EXPECT_EQ(1U, cq_impl_->size());
    cq_impl_->SimulateCompletion(true);
    EXPECT_EQ(0U, cq_impl_->size());
    auto res = res_future.get();
    EXPECT_EQ(google::cloud::StatusCode::kPermissionDenied, res.code());
  }

  std::shared_ptr<MockCompletionQueue> cq_impl_;
  bigtable::CompletionQueue cq_;
  std::shared_ptr<bigtable::testing::MockDataClient> client_;
  std::unique_ptr<bigtable::Table> table_;
};

TEST_F(ValidContextMdAsyncTest, AsyncApply) {
  using ::testing::_;
  bigtable::testing::MockAsyncFailingRpcFactory<bt::MutateRowRequest,
                                                bt::MutateRowResponse>
      rpc_factory;
  EXPECT_CALL(*client_, AsyncMutateRow(_, _, _))
      .WillOnce(::testing::Invoke(rpc_factory.Create(
          R"""(
              table_name: "projects/the-project/instances/the-instance/tables/the-table"
              row_key: "row_key"
              mutations: { delete_from_row { } }
          )""",
          "google.bigtable.v2.Bigtable.MutateRow")));
  FinishTest(table_->AsyncApply(
      bigtable::SingleRowMutation("row_key", bigtable::DeleteFromRow()), cq_));
}

TEST_F(ValidContextMdAsyncTest, AsyncCheckAndMutateRow) {
  using ::testing::_;
  bigtable::testing::MockAsyncFailingRpcFactory<bt::CheckAndMutateRowRequest,
                                                bt::CheckAndMutateRowResponse>
      rpc_factory;
  EXPECT_CALL(*client_, AsyncCheckAndMutateRow(_, _, _))
      .WillOnce(::testing::Invoke(rpc_factory.Create(
          R"""(
              table_name: "projects/the-project/instances/the-instance/tables/the-table"
              row_key: "row_key"
              true_mutations: { delete_from_row { } }
              predicate_filter: { pass_all_filter: true }
          )""",
          "google.bigtable.v2.Bigtable.CheckAndMutateRow")));
  FinishTest(table_->AsyncCheckAndMutateRow(
      "row_key", bigtable::Filter::PassAllFilter(), {bigtable::DeleteFromRow()},
      {}, cq_));
}

TEST_F(ValidContextMdAsyncTest, AsyncReadModifyWriteRow) {
  using ::testing::_;
  bigtable::testing::MockAsyncFailingRpcFactory<bt::ReadModifyWriteRowRequest,
                                                bt::ReadModifyWriteRowResponse>
      rpc_factory;
  EXPECT_CALL(*client_, AsyncReadModifyWriteRow(_, _, _))
      .WillOnce(::testing::Invoke(rpc_factory.Create(
          R"""(
              table_name: "projects/the-project/instances/the-instance/tables/the-table"
              row_key: "row_key"
              rules: {
                  family_name: "fam"
                  column_qualifier: "counter"
                  increment_amount: 1
              }
              rules: {
                  family_name: "fam"
                  column_qualifier: "list"
                  append_value: ";element"
              }
          )""",
          "google.bigtable.v2.Bigtable.ReadModifyWriteRow")));
  FinishTest(table_->AsyncReadModifyWriteRow(
      "row_key", cq_,
      bigtable::ReadModifyWriteRule::IncrementAmount("fam", "counter", 1),
      bigtable::ReadModifyWriteRule::AppendValue("fam", "list", ";element")));
}
