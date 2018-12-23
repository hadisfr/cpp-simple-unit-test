#include "Triangle.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>

class TriangleUnderTest : public Triangle {
public:
  TriangleUnderTest(int side1, int side2, int side3);
  int get_side1() const;
  int get_side2() const;
  int get_side3() const;
};

TriangleUnderTest::TriangleUnderTest(int side1, int side2, int side3)
    : Triangle(side1, side2, side3) {}

int TriangleUnderTest::get_side1() const { return side1; }

int TriangleUnderTest::get_side2() const { return side2; }

int TriangleUnderTest::get_side3() const { return side3; }

class TriangleTest {
private:
  void constructor_happy_test();
  void constructor_inequality_equal_test();
  void constructor_inequality_equal_invalid_order_test();
  void constructor_inequality_reverse_test();
  void constructor_inequality_reverse_invalid_order_test();
  void constructor_second_longest_test();
  void constructor_third_longest_test();
  void get_perimeter_test();
  void get_area_test();
  void get_kind_isosceles_test();
  void get_kind_equilateral_test();
  void get_kind_scalene_test();

public:
  void run();
};

void TriangleTest::constructor_happy_test() {
  TriangleUnderTest triangle(5, 4, 3);
  assert((triangle.get_side1() == 5 && triangle.get_side2() == 4 &&
          triangle.get_side3() == 3));
}

void TriangleTest::constructor_inequality_equal_test() {
  try {
    TriangleUnderTest triangle(10, 4, 6);
    assert(false);
  } catch (std::invalid_argument) {
  }
}

void TriangleTest::constructor_inequality_equal_invalid_order_test() {
  try {
    TriangleUnderTest triangle(4, 10, 6);
    assert(false);
  } catch (std::invalid_argument) {
  }
}

void TriangleTest::constructor_inequality_reverse_test() {
  try {
    TriangleUnderTest triangle(10, 3, 6);
    assert(false);
  } catch (std::invalid_argument) {
  }
}

void TriangleTest::constructor_inequality_reverse_invalid_order_test() {
  try {
    TriangleUnderTest triangle(3, 10, 6);
    assert(false);
  } catch (std::invalid_argument) {
  }
}

void TriangleTest::constructor_second_longest_test() {
  TriangleUnderTest triangle(4, 5, 3);
  assert((triangle.get_side1() == 5 &&
          ((triangle.get_side2() == 4 && triangle.get_side3() == 3) ||
           (triangle.get_side2() == 3 && triangle.get_side3() == 4))));
}

void TriangleTest::constructor_third_longest_test() {
  TriangleUnderTest triangle(4, 3, 5);
  assert((triangle.get_side1() == 5 &&
          ((triangle.get_side2() == 4 && triangle.get_side3() == 3) ||
           (triangle.get_side2() == 3 && triangle.get_side3() == 4))));
}

void TriangleTest::get_perimeter_test() {
  TriangleUnderTest triangle(4, 3, 5);
  assert(triangle.get_perimeter() == 12);
}

void TriangleTest::get_area_test() {
  TriangleUnderTest triangle(4, 3, 5);
  assert(abs(triangle.get_area() - 6) < 0.001);
}

void TriangleTest::get_kind_isosceles_test() {
  TriangleUnderTest triangle(4, 4, 5);
  assert(triangle.get_kind() == Triangle::Kind::ISOSCELES);
}

void TriangleTest::get_kind_equilateral_test() {
  TriangleUnderTest triangle(4, 4, 4);
  assert(triangle.get_kind() == Triangle::Kind::EQUILATERAL);
}

void TriangleTest::get_kind_scalene_test() {
  TriangleUnderTest triangle(4, 3, 5);
  assert(triangle.get_kind() == Triangle::Kind::SCALENE);
}

void TriangleTest::run() {
  constructor_happy_test();
  constructor_inequality_equal_test();
  constructor_inequality_equal_invalid_order_test();
  constructor_inequality_reverse_test();
  constructor_inequality_reverse_invalid_order_test();
  constructor_second_longest_test();
  constructor_third_longest_test();
  get_perimeter_test();
  get_area_test();
  get_kind_isosceles_test();
  get_kind_equilateral_test();
  get_kind_scalene_test();
}

int main(int argc, char const *argv[]) {
  TriangleTest triangle_test;
  triangle_test.run();

  return 0;
}
