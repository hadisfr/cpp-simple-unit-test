#include "get_avg_of_vector.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <cmath>
#include <iostream>

TEST_CASE("happy test") {
  std::vector<int> v = {1, 2};
  REQUIRE(Approx(get_avg_of_vector(v)) == 1.5);
}

TEST_CASE("single element test") {
  std::vector<int> v = {3};
  REQUIRE(Approx(get_avg_of_vector(v)) == 3);
}

TEST_CASE("empty vector test") {
  std::vector<int> v = {};
  REQUIRE_THROWS_AS(get_avg_of_vector(v), std::length_error);
}
