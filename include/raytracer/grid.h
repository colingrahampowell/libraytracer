#ifndef GRID_H
#define GRID_H

#include <cstdint>
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

template <typename T, template<class> class... Mixins>
class grid : public Mixins<grid<T>>...
{
public:
  template <typename = std::enable_if_t<std::is_default_constructible<T>::value>>
  grid(uint32_t width, uint32_t height)
  : p_array(width * height, T()),
    p_width(width)
  {
  }

  grid(uint32_t width, uint32_t height, T fill)
  : p_array(width * height, fill),
    p_width(width)
  {
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

  uint32_t width() const 
  { 
    return p_width; 
  }

  uint32_t height() const 
  { 
    return p_array.size() / p_width;
  }

private:
  void bounds_check_(uint32_t x, uint32_t y) const
  {
    if(!(x < width()) || !(y < height()))
    {
      throw std::out_of_range("Input exceeds array dimensions!");
    }
  }

  std::vector<T> p_array;
  uint32_t p_width;
};
}

#endif
