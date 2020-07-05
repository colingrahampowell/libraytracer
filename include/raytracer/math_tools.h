#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

#include <cstdlib>
#include <type_traits>

namespace raytracer {

// Quick-and-dirty floating-point comparison using an epsilon
template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
bool about_equal(T a, T b, T epsilon = 0.00001) {
  return std::abs(a - b) < epsilon ? true : false;
}
}  // namespace raytracer

#endif  // MATH_TOOLS_H
