#include <gtest/gtest.h>
#include <raytracer/color3.h>
#include <raytracer/math_tools.h>

TEST(Color3Test, Create) {
  const auto c = raytracer::color3(-0.5, 0.4, 1.7);
  EXPECT_TRUE(raytracer::about_equal(c.red(), -0.5F));
  EXPECT_TRUE(raytracer::about_equal(c.green(), 0.4F));
  EXPECT_TRUE(raytracer::about_equal(c.blue(), 1.7F));
}

TEST(Color3Test, Add) {
  const auto c = raytracer::color3(0.9, 0.6, 0.75);
  const auto d = raytracer::color3(0.7, 0.1, 0.25);
  EXPECT_EQ(c + d, raytracer::color3(1.6, 0.7, 1.0));
}

TEST(Color3Test, Subtract) {
  const auto c = raytracer::color3(0.9, 0.6, 0.75);
  const auto d = raytracer::color3(0.7, 0.1, 0.25);
  EXPECT_EQ(c - d, raytracer::color3(0.2, 0.5, 0.5));
}

TEST(Color3Test, Multiply) {
  // using Schur / Hadamard product
  const auto c = raytracer::color3(1.0, 0.2, 0.4);
  const auto d = raytracer::color3(0.9, 1.0, 0.1);
  EXPECT_EQ(c * d, raytracer::color3(0.9, 0.2, 0.04));
}
