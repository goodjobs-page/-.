// Copyright 2018 Google LLC
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

#include "google/cloud/optional.h"
#include "google/cloud/testing_util/testing_types.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
inline namespace GOOGLE_CLOUD_CPP_NS {
/// Helper types to test google::cloud::optional<T>
namespace {

using testing_util::Observable;
using OptionalObservable = optional<Observable>;

TEST(OptionalTest, Simple) {
  optional<int> actual;
  EXPECT_FALSE(actual.has_value());
  EXPECT_FALSE(static_cast<bool>(actual));

  EXPECT_EQ(42, actual.value_or(42));
#if GOOGLE_CLOUD_CPP_HAVE_EXCEPTIONS
  EXPECT_THROW(actual.value(), std::exception);
#else
  EXPECT_DEATH_IF_SUPPORTED(actual.value(), "exceptions are disabled");
#endif  // GOOGLE_CLOUD_CPP_HAVE_EXCEPTIONS

  actual.emplace(24);
  EXPECT_TRUE(actual.has_value());
  EXPECT_TRUE(static_cast<bool>(actual));
  EXPECT_EQ(24, actual.value_or(42));
  EXPECT_EQ(24, actual.value());
}

TEST(OptionalTest, NoDefaultConstruction) {
  Observable::reset_counters();
  OptionalObservable other;
  EXPECT_EQ(0, Observable::default_constructor);
  EXPECT_FALSE(other.has_value());
}

TEST(OptionalTest, Copy) {
  Observable::reset_counters();
  OptionalObservable other(Observable("foo"));
  EXPECT_EQ("foo", other.value().str());
  EXPECT_EQ(1, Observable::move_constructor);

  Observable::reset_counters();
  OptionalObservable copy(other);
  EXPECT_EQ(1, Observable::copy_constructor);
  EXPECT_TRUE(copy.has_value());
  EXPECT_TRUE(other.has_value());
  EXPECT_EQ("foo", copy->str());
}

TEST(OptionalTest, MoveCopy) {
  Observable::reset_counters();
  OptionalObservable other(Observable("foo"));
  EXPECT_EQ("foo", other.value().str());
  EXPECT_EQ(1, Observable::move_constructor);

  Observable::reset_counters();
  OptionalObservable copy(std::move(other));
  EXPECT_EQ(1, Observable::move_constructor);
  EXPECT_TRUE(copy.has_value());
  EXPECT_EQ("foo", copy->str());
  // The spec requires moved-from optionals to have a value, but the value
  // is whatever is left after moving out from the 'T' parameter:
  EXPECT_TRUE(other.has_value());
  EXPECT_EQ("moved-out", other->str());
}

TEST(OptionalTest, MoveAssignment_NoValue_NoValue) {
  OptionalObservable other;
  OptionalObservable assigned;
  EXPECT_FALSE(other.has_value());
  EXPECT_FALSE(assigned.has_value());

  Observable::reset_counters();
  assigned = std::move(other);
  EXPECT_FALSE(other.has_value());
  EXPECT_FALSE(assigned.has_value());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
}

TEST(OptionalTest, MoveAssignment_NoValue_Value) {
  OptionalObservable other(Observable("foo"));
  OptionalObservable assigned;
  EXPECT_TRUE(other.has_value());
  EXPECT_FALSE(assigned.has_value());

  Observable::reset_counters();
  assigned = std::move(other);
  EXPECT_TRUE(other.has_value());
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("moved-out", other->str());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(1, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
}

TEST(OptionalTest, MoveAssignment_NoValue_T) {
  Observable other("foo");
  OptionalObservable assigned;
  EXPECT_FALSE(assigned.has_value());

  Observable::reset_counters();
  assigned = std::move(other);
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("moved-out", other.str());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(1, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
}

TEST(OptionalTest, MoveAssignment_Value_NoValue) {
  OptionalObservable other;
  OptionalObservable assigned(Observable("bar"));
  EXPECT_FALSE(other.has_value());
  EXPECT_TRUE(assigned.has_value());

  Observable::reset_counters();
  assigned = std::move(other);
  EXPECT_FALSE(other.has_value());
  EXPECT_FALSE(assigned.has_value());
  EXPECT_EQ(1, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
}

TEST(OptionalTest, MoveAssignment_Value_Value) {
  OptionalObservable other(Observable("foo"));
  OptionalObservable assigned(Observable("bar"));
  EXPECT_TRUE(other.has_value());
  EXPECT_TRUE(assigned.has_value());

  Observable::reset_counters();
  assigned = std::move(other);
  EXPECT_TRUE(other.has_value());
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(1, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("moved-out", other->str());
}

TEST(OptionalTest, MoveAssignment_Value_T) {
  Observable other("foo");
  OptionalObservable assigned(Observable("bar"));
  EXPECT_TRUE(assigned.has_value());

  Observable::reset_counters();
  assigned = std::move(other);
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(1, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("moved-out", other.str());
}

TEST(OptionalTest, CopyAssignment_NoValue_NoValue) {
  OptionalObservable other;
  OptionalObservable assigned;
  EXPECT_FALSE(other.has_value());
  EXPECT_FALSE(assigned.has_value());

  Observable::reset_counters();
  assigned = other;
  EXPECT_FALSE(other.has_value());
  EXPECT_FALSE(assigned.has_value());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
}

TEST(OptionalTest, CopyAssignment_NoValue_Value) {
  OptionalObservable other(Observable("foo"));
  OptionalObservable assigned;
  EXPECT_TRUE(other.has_value());
  EXPECT_FALSE(assigned.has_value());

  Observable::reset_counters();
  assigned = other;
  EXPECT_TRUE(other.has_value());
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("foo", other->str());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(1, Observable::copy_constructor);
}

TEST(OptionalTest, CopyAssignment_NoValue_T) {
  Observable other("foo");
  OptionalObservable assigned;
  EXPECT_FALSE(assigned.has_value());

  Observable::reset_counters();
  assigned = other;
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("foo", other.str());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(1, Observable::copy_constructor);
}

TEST(OptionalTest, CopyAssignment_Value_NoValue) {
  OptionalObservable other;
  OptionalObservable assigned(Observable("bar"));
  EXPECT_FALSE(other.has_value());
  EXPECT_TRUE(assigned.has_value());

  Observable::reset_counters();
  assigned = other;
  EXPECT_FALSE(other.has_value());
  EXPECT_FALSE(assigned.has_value());
  EXPECT_EQ(1, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(0, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
}

TEST(OptionalTest, CopyAssignment_Value_Value) {
  OptionalObservable other(Observable("foo"));
  OptionalObservable assigned(Observable("bar"));
  EXPECT_TRUE(other.has_value());
  EXPECT_TRUE(assigned.has_value());

  Observable::reset_counters();
  assigned = other;
  EXPECT_TRUE(other.has_value());
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(1, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("foo", other->str());
}

TEST(OptionalTest, CopyAssignment_Value_T) {
  Observable other("foo");
  OptionalObservable assigned(Observable("bar"));
  EXPECT_TRUE(assigned.has_value());

  Observable::reset_counters();
  assigned = other;
  EXPECT_TRUE(assigned.has_value());
  EXPECT_EQ(0, Observable::destructor);
  EXPECT_EQ(0, Observable::move_assignment);
  EXPECT_EQ(1, Observable::copy_assignment);
  EXPECT_EQ(0, Observable::move_constructor);
  EXPECT_EQ(0, Observable::copy_constructor);
  EXPECT_EQ("foo", assigned->str());
  EXPECT_EQ("foo", other.str());
}

TEST(OptionalTest, MoveValue) {
  OptionalObservable other(Observable("foo"));
  EXPECT_EQ("foo", other.value().str());

  Observable::reset_counters();
  auto observed = std::move(other).value();
  EXPECT_EQ("foo", observed.str());
  // The optional should still have a value, but its value should have been
  // moved out.
  EXPECT_TRUE(other.has_value());
  EXPECT_EQ("moved-out", other->str());
}

TEST(OptionalTest, MoveValueOr) {
  OptionalObservable other(Observable("foo"));
  EXPECT_EQ("foo", other.value().str());

  auto observed = std::move(other).value_or(Observable("bar"));
  EXPECT_EQ("foo", observed.str());
  // The optional should still have a value, but its value should have been
  // moved out.
  EXPECT_TRUE(other.has_value());
  EXPECT_EQ("moved-out", other->str());
}

TEST(OptionalTest, WithNoDefaultConstructor) {
  using TestedOptional = optional<testing_util::NoDefaultConstructor>;
  TestedOptional empty;
  EXPECT_FALSE(empty.has_value());

  TestedOptional actual(testing_util::NoDefaultConstructor(std::string("foo")));
  EXPECT_TRUE(actual.has_value());
  EXPECT_EQ(actual->str(), "foo");
}
}  // namespace
}  // namespace GOOGLE_CLOUD_CPP_NS
}  // namespace cloud
}  // namespace google
