#ifndef VEC4_H
#define VEC4_H

#include <raytracer/math_tools.h>

#include <cmath>
#include <type_traits>

namespace raytracer {

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
class vec4 {
 public:
  vec4(T x, T y, T z, T w) : p_x(x), p_y(y), p_z(z), p_w(w) {}

  T x() const { return p_x; }
  T y() const { return p_y; }
  T z() const { return p_z; }
  T w() const { return p_w; }

  // Comparison
  bool operator==(const vec4& other) const {
    if (about_equal(p_x, other.p_x) && about_equal(p_y, other.p_y) &&
        about_equal(p_z, other.p_z) && about_equal(p_w, other.p_w)) {
      return true;
    }
    return false;
  }

  // Arithmetic operators:
  vec4 operator+(const vec4& other) const {
    return vec4(p_x + other.p_x, p_y + other.p_y, p_z + other.p_z,
                p_w + other.p_w);
  }

  vec4 operator-(const vec4& other) const {
    return vec4(p_x - other.p_x, p_y - other.p_y, p_z - other.p_z,
                p_w - other.p_w);
  }

  vec4 operator*(T scalar) const {
    return vec4(p_x * scalar, p_y * scalar, p_z * scalar, p_w * scalar);
  }

  vec4 operator/(T scalar) const {
    return vec4(p_x / scalar, p_y / scalar, p_z / scalar, p_w / scalar);
  }

  vec4 operator-() const { return *this * -1; }

 private:
  T p_x, p_y, p_z, p_w;
};

using vec4d = vec4<double>;
using vec4f = vec4<float>;

}  // namespace raytracer
#endif 
