#ifndef GRID_H
#define GRID_H

#include <array>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace raytracer
{
template <typename T>
class range
{
public:
  range(T* start, T* end, uint32_t stride = sizeof(ptrdiff_t))
  : p_start(start),
    p_end(end),
    p_stride(stride)
  {
  }

  // TODO: implement begin() and end()
private:
  T* p_start;
  T* p_end;
  uint32_t p_stride;
};

template <typename T, 
          uint32_t Width, 
          uint32_t Height, 
          template<class> class... Mixins>
class grid : public Mixins<grid<T, Width, Height>>...
{
public:
  grid()
  {
  }

  grid(T fill_value)
  {
    p_array.fill(fill_value);
  }

  grid(std::array<T, Width * Height>&&  list)
  : p_array(list)
  {
  }

  grid& operator=(const grid& other)
  {
    p_array = other.p_array;
    return *this;
  }

  T operator()(uint32_t x, uint32_t y) const
  {
    bounds_check_(x, y);
    return p_array.at(x + y * width());
  }

  T& operator()(uint32_t x, uint32_t y)
  {
    bounds_check_(x, y);
    return p_array.at(x + y * width());
  }

  range<T> row(uint32_t rownum) const
  {
    bounds_check_(0, rownum);
    const auto start = rownum * width();
    return range<T>(start, start + width());
  }

  range<T> column(uint32_t colnum) const
  {
    bounds_check_(colnum, 0);
    const auto end = colnum + width() * height(); // past-the-end
    return range<T>(colnum, end, width());
  }

  constexpr uint32_t width() const 
  { 
    return Width; 
  }

  constexpr uint32_t height() const 
  { 
    return p_array.size() / Width;
  }

private:
  void bounds_check_(uint32_t x, uint32_t y) const
  {
    if(!(x < width()) || !(y < height()))
    {
      throw std::out_of_range("Input exceeds array dimensions!");
    }
  }

  std::array<T, Width * Height> p_array;
};
}

#endif
