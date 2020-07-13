#include <gtest/gtest.h>
#include <raytracer/math_tools.h>
#include <raytracer/vec3.h>

// SCENARIO: Adding two vectors
TEST(Vec3Test, AddVectors) {
  const auto a1 = raytracer::vec3d(3, -2, 5);
  const auto a2 = raytracer::vec3d(-2, 3, 1);

  EXPECT_EQ(a1 + a2, raytracer::vec3d(1, 1, 6));
}

// SCENARIO: Subtracting two vectors
TEST(Vec3Test, SubtractVectors) {
  const auto p1 = raytracer::vec3d(3, 2, 1);
  const auto p2 = raytracer::vec3d(5, 6, 7);

  EXPECT_EQ(p1 - p2, raytracer::vec3d(-2, -4, -6));
}

// SCENARIO: Negating a vector
TEST(Vec3Test, Negate) {
  const auto a = raytracer::vec3d(1, -2, 3);
  const auto neg_a = -a;

  EXPECT_EQ(neg_a.x(), -a.x());
  EXPECT_EQ(neg_a.y(), -a.y());
  EXPECT_EQ(neg_a.z(), -a.z());
}

// SCENARIO: Multiplying a vector by a scalar
TEST(Vec3Test, MultiplyScalar) {
  const auto a = raytracer::vec3d(1, -2, 3);
  EXPECT_EQ(a * 3.5, raytracer::vec3d(3.5, -7, 10.5));
}

// SCENARIO: Multiplying a vector by a fraction
TEST(Vec3Test, MultiplyFraction) {
  const auto a = raytracer::vec3d(1, -2, 3);
  EXPECT_EQ(a * 0.5, raytracer::vec3d(0.5, -1, 1.5));
}

// SCENARIO: Divide vector by a scalar
TEST(Vec3Test, DivideScalar) {
  const auto a = raytracer::vec3d(1, -2, 3);
  EXPECT_EQ(a / 2, raytracer::vec3d(0.5, -1, 1.5));
}

// SCENARIO: Magnitude of vector (1,0,0)
TEST(Vec3Test, MagnitudeX) {
  const auto v = raytracer::vec3d(1, 0, 0);
  EXPECT_TRUE(raytracer::about_equal(v.magnitude(), 1.0));
}

// SCENARIO: Magnitude of vector (0,1,0)
TEST(Vec3Test, MagnitudeY) {
  const auto v = raytracer::vec3d(0, 1, 0);
  EXPECT_TRUE(raytracer::about_equal(v.magnitude(), 1.0));
}

// SCENARIO: Magnitude of vector (0,0,1,0)
TEST(Vec3Test, MagnitudeZ) {
  const auto v = raytracer::vec3d(0, 0, 1);
  EXPECT_TRUE(raytracer::about_equal(v.magnitude(), 1.0));
}

// SCENARIO: Magnitude of vector (1,2,3)
TEST(Vec3Test, MagnitudePositive) {
  const auto v = raytracer::vec3d(1, 2, 3);
  EXPECT_TRUE(raytracer::about_equal(v.magnitude(), std::sqrt(14)));
}

// SCENARIO: Magnitude of vector (-1,-2,-3)
TEST(Vec3Test, MagnitudeNegative) {
  const auto v = raytracer::vec3d(-1, -2, -3);
  EXPECT_TRUE(raytracer::about_equal(v.magnitude(), std::sqrt(14)));
}

TEST(Vec3Test, NormalizeX) {
  const auto v = raytracer::vec3d(4, 0, 0);
  EXPECT_EQ(v.normalize(), raytracer::vec3d(1, 0, 0));
}

TEST(Vec3Test, NormalizePositive) {
  const auto v = raytracer::vec3d(1, 2, 3);
  EXPECT_EQ(v.normalize(),
            raytracer::vec3d(1 / std::sqrt(14), 2 / std::sqrt(14),
                             3 / std::sqrt(14)));
}

TEST(Vec3Test, NormalizeNegative) {
  const auto v = raytracer::vec3d(-1, -2, -3);
  EXPECT_EQ(v.normalize(),
            raytracer::vec3d(-1 / std::sqrt(14), -2 / std::sqrt(14),
                             -3 / std::sqrt(14)));
}

TEST(Vec3Test, NormalizeMagnitude) {
  const auto v = raytracer::vec3d(1, 2, 3);
  const auto v_norm = v.normalize();
  EXPECT_TRUE(raytracer::about_equal(v_norm.magnitude(), 1.0));
}

TEST(Vec3Test, DotProduct) {
  const auto v = raytracer::vec3d(1, 2, 3);
  const auto w = raytracer::vec3d(2, 3, 4);
  EXPECT_TRUE(raytracer::about_equal(v.dot(w), 20.0));
}
