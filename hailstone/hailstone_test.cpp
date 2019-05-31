#include "hailstone.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <limits>

TEST_CASE("0 does not satisfies Hailstone") { CHECK(!satisfies_hailstone(0)); }

TEST_CASE("all posetive numbers satisfy Hailstone") {
  CHECK(satisfies_hailstone(1));
  CHECK(satisfies_hailstone(10));
  CHECK(
      satisfies_hailstone(std::numeric_limits<unsigned long long>::max() / 3));
}
