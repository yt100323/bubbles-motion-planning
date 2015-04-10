/*
 * Copyright (C) 2015 Hamza Merzić
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SimpleTreeTest

#include "simple_tree.h"

#include <vector>
#include <memory>
#include <cmath>

#include "environment/pqp_environment.h"
#include "random_generator/naive_generator.h"
#include <boost/test/unit_test.hpp>

typedef Eigen::VectorXd EVectorXd;

BOOST_AUTO_TEST_CASE(try_connect) {
  std::vector<std::pair<double, double>> limits;
  limits.emplace_back(0, 2 * M_PI);
  limits.emplace_back(0, 2 * M_PI);
  std::unique_ptr<RandomSpaceGeneratorInterface> generator (
    new NaiveGenerator(limits));
  PqpEnvironment* pqp (new PqpEnvironment(
      {"models/robot1_seg1.stl", "models/robot1_seg2.stl"},
      "models/dh_table_test.txt","models/obstacles_test.stl",
      generator.get()));

  EVectorXd start (2); start << 0, 0;
  EVectorXd end (2); end << 1, 1;
  SimpleTree simple_tree (pqp, start, end, 0.01);
  EVectorXd qbegin (2); qbegin << 0, 0;
  EVectorXd qend (2); qend << 1, 1;
  BOOST_CHECK_EQUAL(simple_tree.TryConnect(qbegin, qend), true);
}

BOOST_AUTO_TEST_CASE(try_connect1) {
  std::vector<std::pair<double, double>> limits;
  limits.emplace_back(0, 2 * M_PI);
  limits.emplace_back(0, 2 * M_PI);
  std::unique_ptr<RandomSpaceGeneratorInterface> generator (
    new NaiveGenerator(limits));
  PqpEnvironment* pqp (new PqpEnvironment(
      {"models/robot1_seg1.stl", "models/robot1_seg2.stl"},
      "models/dh_table_test.txt","models/obstacles_test.stl",
      generator.get()));

  EVectorXd start (2); start << 0, 0;
  EVectorXd end (2); end << 1, 1;
  SimpleTree simple_tree (pqp, start, end, 0.01);
  EVectorXd qbegin (2); qbegin << M_PI_2 - 0.1, M_PI_2 - 0.1;
  EVectorXd qend (2); qend << M_PI_2 + 0.1, M_PI_2 + 0.1;
  BOOST_CHECK_EQUAL(simple_tree.TryConnect(qbegin, qend), false);
  BOOST_CHECK_EQUAL(simple_tree.BuildTree(), true);
}