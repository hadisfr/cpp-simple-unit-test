#include "Triangle.hpp"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
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

TEST_CASE("constructor happy test") {
  TriangleUnderTest triangle(5, 4, 3);
  REQUIRE((triangle.get_side1() == 5 && triangle.get_side2() == 4 &&
           triangle.get_side3() == 3));
}

TEST_CASE("constructor inequality equal test") {
  REQUIRE_THROWS_AS(TriangleUnderTest(10, 4, 6), std::invalid_argument);
}

TEST_CASE("constructor inequality equal invalid order test") {
  REQUIRE_THROWS_AS(TriangleUnderTest(4, 10, 6), std::invalid_argument);
}

TEST_CASE("constructor inequality reverse test") {
  REQUIRE_THROWS_AS(TriangleUnderTest(10, 3, 6), std::invalid_argument);
}

TEST_CASE("constructor inequality reverse invalid order test") {
  REQUIRE_THROWS_AS(TriangleUnderTest(3, 10, 6), std::invalid_argument);
}

TEST_CASE("constructor second longest test") {
  TriangleUnderTest triangle(4, 5, 3);
  REQUIRE((triangle.get_side1() == 5 &&
           ((triangle.get_side2() == 4 && triangle.get_side3() == 3) ||
            (triangle.get_side2() == 3 && triangle.get_side3() == 4))));
}

TEST_CASE("constructor third longest test") {
  TriangleUnderTest triangle(4, 3, 5);
  REQUIRE((triangle.get_side1() == 5 &&
           ((triangle.get_side2() == 4 && triangle.get_side3() == 3) ||
            (triangle.get_side2() == 3 && triangle.get_side3() == 4))));
}

TEST_CASE("get_perimeter test") {
  TriangleUnderTest triangle(4, 3, 5);
  REQUIRE(triangle.get_perimeter() == 12);
}

TEST_CASE("get_area test") {
  TriangleUnderTest triangle(4, 3, 5);
  REQUIRE(abs(triangle.get_area() - 6) < 0.001);
}

TEST_CASE("get_kind isosceles test") {
  TriangleUnderTest triangle(4, 4, 5);
  REQUIRE(triangle.get_kind() == Triangle::Kind::ISOSCELES);
}

TEST_CASE("get_kind equilateral test") {
  TriangleUnderTest triangle(4, 4, 4);
  REQUIRE(triangle.get_kind() == Triangle::Kind::EQUILATERAL);
}

TEST_CASE("get_kind scalene test") {
  TriangleUnderTest triangle(4, 3, 5);
  REQUIRE(triangle.get_kind() == Triangle::Kind::SCALENE);
}
