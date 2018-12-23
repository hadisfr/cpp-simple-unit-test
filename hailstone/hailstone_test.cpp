#include "hailstone.hpp"
#include <cassert>
#include <limits>

int main(int argc, char const *argv[]) {
  assert(satisfies_hailstone(10));
  assert(satisfies_hailstone(0));
  assert(
      satisfies_hailstone(std::numeric_limits<unsigned long long>::max() / 3));
  return 0;
}
