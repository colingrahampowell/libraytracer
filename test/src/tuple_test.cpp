#include <gtest/gtest.h>
#include <raytracer/math_tools.h>
#include <raytracer/tuple.h>

// SCENARIO: A tuple with w = 1.0 is a point
TEST(TupleTest, TupleAsPoint) {
  const auto a = raytracer::tuple_d(4.3, -4.2, 3.1, 1.0);

  EXPECT_TRUE(raytracer::about_equal(a.x(), 4.3));
  EXPECT_TRUE(raytracer::about_equal(a.y(), -4.2));
  EXPECT_TRUE(raytracer::about_equal(a.z(), 3.1));
  EXPECT_TRUE(raytracer::about_equal(a.w(), 1.0));

  EXPECT_EQ(a.type(), raytracer::tuple_type::point);
  EXPECT_NE(a.type(), raytracer::tuple_type::vector);
}

// SCENARIO: A tuple with w = 0.0 is a vector
TEST(TupleTest, TupleAsVector) {
  const auto a = raytracer::tuple_d(4.3, -4.2, 3.1, 0.0);

  EXPECT_TRUE(raytracer::about_equal(a.x(), 4.3));
  EXPECT_TRUE(raytracer::about_equal(a.y(), -4.2));
  EXPECT_TRUE(raytracer::about_equal(a.z(), 3.1));
  EXPECT_TRUE(raytracer::about_equal(a.w(), 0.0));

  EXPECT_EQ(a.type(), raytracer::tuple_type::vector);
  EXPECT_NE(a.type(), raytracer::tuple_type::point);
}

// SCENARIO: create_point() creates tuples with w = 1.0
TEST(TupleTest, CreatePoint) {
  const auto p = raytracer::tuple_d::make_point(4, -4, 3);
  const auto t = raytracer::tuple_d(4, -4, 3, 1.0);

  EXPECT_EQ(p, t);
}

// SCENARIO: create_vector() creats tuples with w = 0.0
TEST(TupleTest, CreateVector) {
  const auto v = raytracer::tuple_d::make_vector(4, -4, 3);
  const auto t = raytracer::tuple_d(4, -4, 3, 0.0);

  EXPECT_EQ(v, t);
}

// SCENARIO: Adding two tuples
TEST(TupleTest, AddVectorToPoint) {
  const auto a1 = raytracer::tuple_d(3, -2, 5, 1);
  const auto a2 = raytracer::tuple_d(-2, 3, 1, 0);

  EXPECT_EQ(a1 + a2, raytracer::tuple_d(1, 1, 6, 1));
}

// SCENARIO: Subtracting two points
TEST(TupleTest, SubtractPoints) {
  const auto p1 = raytracer::tuple_d::make_point(3, 2, 1);
  const auto p2 = raytracer::tuple_d::make_point(5, 6, 7);

  EXPECT_EQ(p1 - p2, raytracer::tuple_d::make_vector(-2, -4, -6));
}

// SCENARIO: Subtracting a vector from a point
TEST(TupleTest, SubtractVectorFromPoint) {
  const auto p = raytracer::tuple_d::make_point(3, 2, 1);
  const auto v = raytracer::tuple_d::make_vector(5, 6, 7);
  EXPECT_EQ(p - v, raytracer::tuple_d::make_point(-2, -4, -6));
}

// SCENARIO: Subtracting two vectors
TEST(TupleTest, SubtractTwoVectors) {
  const auto v1 = raytracer::tuple_d::make_vector(3, 2, 1);
  const auto v2 = raytracer::tuple_d::make_vector(5, 6, 7);
  EXPECT_EQ(v1 - v2, raytracer::tuple_d::make_vector(-2, -4, -6));
}

// SCENARIO: Negating a tuple
TEST(TupleTest, Negate) {
  const auto a = raytracer::tuple_d(1, -2, 3, -4);
  const auto neg_a = -a;

  EXPECT_EQ(neg_a.x(), -a.x());
  EXPECT_EQ(neg_a.y(), -a.y());
  EXPECT_EQ(neg_a.z(), -a.z());
  EXPECT_EQ(neg_a.w(), -a.w());
}

// SCENARIO: Multiplying a tuple by a scalar
TEST(TupleTest, MultiplyScalar) {
  const auto a = raytracer::tuple_d(1, -2, 3, -4);
  EXPECT_EQ(a * 3.5, raytracer::tuple_d(3.5, -7, 10.5, -14));
}

// SCENARIO: Multiplying a tuple by a fraction
TEST(TupleTest, MultiplyFraction) {
  const auto a = raytracer::tuple_d(1, -2, 3, -4);
  EXPECT_EQ(a * 0.5, raytracer::tuple_d(0.5, -1, 1.5, -2));
}

// SCENARIO: Divide tuple by a scalar
TEST(TupleTest, DivideScalar) {
  const auto a = raytracer::tuple_d(1, -2, 3, -4);
  EXPECT_EQ(a / 2, raytracer::tuple_d(0.5, -1, 1.5, -2));
}
