#include <gtest/gtest.h>
#include <raytracer/grid.h>

TEST(GridTest, Construct)
{
  raytracer::grid<uint32_t, 4, 5> arr;
  EXPECT_EQ(arr.width(), 4);
  EXPECT_EQ(arr.height(), 5);
}

TEST(GridTest, ConstructWithFill)
{
  raytracer::grid<uint32_t, 4, 5> arr(42);
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

TEST(GridTest, GetAndSetValue)
{
  raytracer::grid<uint32_t, 3, 4> arr(15);
  EXPECT_NE(arr(1,2), 42);
  arr(1,2) = 42;
  EXPECT_EQ(arr(1,2), 42);
}

TEST(GridTest, CopyAssign)
{
  const auto arr = raytracer::grid<uint32_t,3,1>({4,5,6});
  EXPECT_EQ(arr(0,0), 4);
  EXPECT_EQ(arr(1,0), 5);
  EXPECT_EQ(arr(2,0), 6);
}

TEST(GridTest, ConstructWithArray)
{
  raytracer::grid<uint32_t,3,1> arr({4,5,6});
  EXPECT_EQ(arr(0,0), 4);
  EXPECT_EQ(arr(1,0), 5);
  EXPECT_EQ(arr(2,0), 6);
}

TEST(GridTest, GetAndSetOutOfBounds)
{
  raytracer::grid<uint32_t, 1, 3> arr;
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

TEST(GridTest, RowIterator)
{
  raytracer::grid<uint32_t, 2, 4> arr;
  constexpr auto new_val = 42;
  EXPECT_NE(arr(0, 1), new_val);
  EXPECT_NE(arr(1, 1), new_val);

  auto my_row = arr.row(1);
  uint32_t i = 0;
  for(auto& elem : my_row)
  {
    elem = new_val;
  }

  EXPECT_EQ(arr(0, 1), new_val);
  EXPECT_EQ(arr(1, 1), new_val);
}

// Iterating last row will set end() as
// a value beyond the end of the grid -
// ensure that past-the-end operator works
// in this case
TEST(GridTest, RowIteratorLastRow)
{
  raytracer::grid<uint32_t, 2, 2> arr;
  constexpr auto new_val = 42;
  EXPECT_NE(arr(0, 1), new_val);
  EXPECT_NE(arr(1, 1), new_val);

  auto my_row = arr.row(1);
  uint32_t i = 0;
  for(auto& elem : my_row)
  {
    elem = new_val;
  }

  EXPECT_EQ(arr(0, 1), new_val);
  EXPECT_EQ(arr(1, 1), new_val);
}

TEST(GridTest, ColIterator)
{
  raytracer::grid<uint32_t, 2, 4> arr;
  constexpr auto new_val = 42;
  EXPECT_NE(arr(0, 1), new_val);
  EXPECT_NE(arr(1, 1), new_val);
  EXPECT_NE(arr(1, 2), new_val);
  EXPECT_NE(arr(1, 3), new_val);

  auto my_col = arr.column(1);
  for(auto& elem : my_col)
  {
    elem = new_val;
  }

  EXPECT_EQ(arr(1, 0), new_val);
  EXPECT_EQ(arr(1, 1), new_val);
  EXPECT_EQ(arr(1, 2), new_val);
  EXPECT_EQ(arr(1, 3), new_val);
}
