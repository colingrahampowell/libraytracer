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
class grid_iter
{
public:
  grid_iter(T* start, T* end, uint32_t stride_elems = 1)
  : p_pos(start),
    p_end(end),
    p_stride(stride_elems)
  {
  }

  struct iterator
  {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;

    iterator(pointer pos_, uint32_t stride_)
    : pos(pos_),
      stride(stride_)
    {
    }

    reference operator*() const
    {
      return *pos;
    }

    pointer operator->() 
    {
      return pos;
    }

    // prefix operator
    iterator& operator++()
    {
      pos += stride;
      return *this;
    }
    
    // postfix operator
    iterator& operator++(int)
    {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const iterator& a, const iterator& b)
    {
      return a.pos == b.pos;
    }

    friend bool operator!=(const iterator& a, const iterator& b)
    {
      return a.pos != b.pos;
    }

    pointer pos; 
    const uint32_t stride;
  };

  iterator begin() 
  {
    return iterator(p_pos, p_stride);
  }

  iterator end()
  {
    return iterator(p_end, p_stride);
  }

private:
  T* p_pos;
  T* p_end;
  const uint32_t p_stride;
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

  grid(std::array<T, Width * Height>&& list)
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

  grid_iter<T> row(uint32_t rownum)
  {
    bounds_check_(0, rownum);
    const auto start_idx = rownum * width();
    const auto end_idx = start_idx + width();
    // second argument is past-the-end, intentionally avoiding bounds check
    return grid_iter<T>(&p_array.at(start_idx), &p_array[end_idx]);
  }

  grid_iter<T> column(uint32_t colnum)
  {
    bounds_check_(colnum, 0);
    const auto start_idx = colnum;
    const auto end_idx = colnum + width() * height(); 
    // second argument is past-the-end, intentionally avoiding bounds check
    return grid_iter<T>(&p_array.at(start_idx), &p_array[end_idx], width());
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
