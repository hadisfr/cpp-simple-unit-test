#include "get_avg_of_vector.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

class GetAvgOfVectorTest {
private:
  void happy_test();
  void single_element_test();
  void empty_vector_test();

public:
  void run();
};

void GetAvgOfVectorTest::happy_test() {
  std::vector<int> v = {1, 2};
  assert(abs(get_avg_of_vector(v) - 1.5) < 0.001);
}

void GetAvgOfVectorTest::single_element_test() {
  std::vector<int> v = {3};
  assert(abs(get_avg_of_vector(v) - 3) < 0.001);
}

void GetAvgOfVectorTest::empty_vector_test() {
  std::vector<int> v = {};
  try {
    float f = get_avg_of_vector(v);
    assert(false && "Empty vector should raise std::length_error");
  } catch (std::length_error) {
  }
}

void GetAvgOfVectorTest::run() {
  happy_test();
  single_element_test();
  empty_vector_test();
}

int main(int argc, char const *argv[]) {
  GetAvgOfVectorTest get_avg_of_vector_test;
  get_avg_of_vector_test.run();

  return 0;
}
