// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>

#include <mesos/mesos.hpp>
#include <mesos/resources.hpp>

#include "fuzz.hpp"

using namespace mesos;
using namespace mesos::internal;

class RamFuzzTest : public ::testing::Test {
protected:
  static ramfuzz::runtime::gen rfg;
};

ramfuzz::runtime::gen RamFuzzTest::rfg;
unsigned ramfuzz::runtime::spinlimit = 3;

using RamFuzz_HTTPTest = RamFuzzTest;

TEST_F(RamFuzz_HTTPTest, ModelResources)
{
  rfg.make<Resources>(rfg.or_subclass);

  // Invariant: resources are grouped by (name, revocation) in a Resources
  // object.  There should be exactly one Resources element (between begin() and
  // end()) for each distinct (name, revocation) pair put into the object.
  //  - operations that add name/revocation pairs: text parsing, +, +=, -, -=

  // Invariant: a group's value is a particular combo of members' values.

  // Invariant: JSON model is an array of name*:value pairs, where name* may
  // include "_revocable".
  //  - obvious problem: a resource's original name may end with "_revocable";
  //    negligible, as humans pick those names
}
