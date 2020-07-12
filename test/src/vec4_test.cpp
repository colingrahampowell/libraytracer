#include <gtest/gtest.h>
#include <raytracer/math_tools.h>
#include <raytracer/vec4.h>

// SCENARIO: Adding two vectors
TEST(Vec4Test, AddVectors) {
  const auto a1 = raytracer::vec4d(3, -2, 5, 1);
  const auto a2 = raytracer::vec4d(-2, 3, 1, 0);

  EXPECT_EQ(a1 + a2, raytracer::vec4d(1, 1, 6, 1));
}

// SCENARIO: Subtracting two vectors
TEST(Vec4Test, SubtractVectors) {
  const auto p1 = raytracer::vec4d(3, 2, 1, 3);
  const auto p2 = raytracer::vec4d(5, 6, 7, 4);

  EXPECT_EQ(p1 - p2, raytracer::vec4d(-2, -4, -6, -1));
}

// SCENARIO: Negating a vector
TEST(Vec4Test, Negate) {
  const auto a = raytracer::vec4d(1, -2, 3, -4);
  const auto neg_a = -a;

  EXPECT_EQ(neg_a.x(), -a.x());
  EXPECT_EQ(neg_a.y(), -a.y());
  EXPECT_EQ(neg_a.z(), -a.z());
  EXPECT_EQ(neg_a.w(), -a.w());
}

// SCENARIO: Multiplying a vector by a scalar
TEST(Vec4Test, MultiplyScalar) {
  const auto a = raytracer::vec4d(1, -2, 3, -4);
  EXPECT_EQ(a * 3.5, raytracer::vec4d(3.5, -7, 10.5, -14));
}

// SCENARIO: Multiplying a vector by a fraction
TEST(Vec4Test, MultiplyFraction) {
  const auto a = raytracer::vec4d(1, -2, 3, -4);
  EXPECT_EQ(a * 0.5, raytracer::vec4d(0.5, -1, 1.5, -2));
}

// SCENARIO: Divide vector by a scalar
TEST(Vec4Test, DivideScalar) {
  const auto a = raytracer::vec4d(1, -2, 3, -4);
  EXPECT_EQ(a / 2, raytracer::vec4d(0.5, -1, 1.5, -2));
}
