#include <gtest/gtest.h>
#include <raytracer/array_2d.h>

TEST(Array2DTest, Construct)
{
  raytracer::array_2d<uint32_t> arr(4, 5);
  EXPECT_EQ(arr.width(), 4);
  EXPECT_EQ(arr.height(), 5);
}

TEST(Array2DTest, ConstructWithFill)
{
  raytracer::array_2d<uint32_t> arr(4, 5, 42);
  EXPECT_EQ(arr.width(), 4);
  EXPECT_EQ(arr.height(), 5);

  // avoid special iterators to focus test as much as possible
  for(uint32_t y = 0; y < arr.height(); ++y)
  {
    for(uint32_t x = 0; x < arr.width(); ++x)
    {
      EXPECT_EQ(arr(x, y), 42);
    }
  }
}

TEST(Array2DTest, GetAndSetValue)
{
  raytracer::array_2d<uint32_t> arr(3,4,15);
  EXPECT_NE(arr(1,2), 42);
  arr(1,2) = 42;
  EXPECT_EQ(arr(1,2), 42);
}

TEST(Array2DTest, GetAndSetOutOfBounds)
{
  raytracer::array_2d<uint32_t> arr(1,3);
  const auto try_out_of_bounds = [&arr](uint32_t x, uint32_t y)
  {
    try 
    {
      arr(x,y);
      FAIL() << "Expected std::out_of_range error";
    }
    catch(const std::out_of_range& err)
    {
      EXPECT_EQ(err.what(), std::string("Input exceeds array dimensions!"));
    }
    catch(...)
    {
      FAIL() << "Expected std::out_of_range error";
    }
  };
  
  // try out of bounds, invalid x-param
  try_out_of_bounds(2, 1);
  // try out of bounds, x-param off by one
  try_out_of_bounds(1, 2);
  
  // try out of bounds, invalid y-param
  try_out_of_bounds(0, 4);
  // try out of bounds, y-param off by one
  try_out_of_bounds(0, 3);
}

