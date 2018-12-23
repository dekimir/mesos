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

#include <memory>

#include <gtest/gtest.h>
#include <mesos/mesos.hpp>
#include <mesos/resources.hpp>

#include "fuzz.hpp"

using namespace mesos;
using namespace mesos::internal;
using namespace ramfuzz::runtime;
using namespace std;

extern unique_ptr<gen> global_gen;

unsigned ramfuzz::runtime::spinlimit = 3;

using RamFuzz_HTTPTest = ::testing::Test;

TEST_F(RamFuzz_HTTPTest, ModelResources)
{
  global_gen->make<Resources>(33, global_gen->or_subclass);
}
