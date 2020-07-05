#ifndef TUPLE_H
#define TUPLE_H

#include <raytracer/math_tools.h>

#include <cmath>
#include <type_traits>

namespace raytracer {

enum class tuple_type { unknown, vector, point };

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
class tuple {
 public:
  tuple(T x, T y, T z, T w) : p_x(x), p_y(y), p_z(z), p_w(w) {}

  tuple_type type() const {
    if (about_equal(p_w, 0.0)) {
      return tuple_type::vector;
    }
    if (about_equal(p_w, 1.0)) {
      return tuple_type::point;
    }
    return tuple_type::unknown;
  }

  static tuple make_vector(T x, T y, T z) { return tuple<T>(x, y, z, 0.0); }
  static tuple make_point(T x, T y, T z) { return tuple<T>(x, y, z, 1.0); }

  T x() const { return p_x; }
  T y() const { return p_y; }
  T z() const { return p_z; }
  T w() const { return p_w; }

  // Comparison
  bool operator==(const tuple& other) const {
    if (about_equal(p_x, other.p_x) && about_equal(p_y, other.p_y) &&
        about_equal(p_z, other.p_z) && about_equal(p_w, other.p_w)) {
      return true;
    }
    return false;
  }

  // Arithmetic operators:
  tuple operator+(const tuple& other) const {
    return tuple(p_x + other.p_x, p_y + other.p_y, p_z + other.p_z,
                 p_w + other.p_w);
  }

  tuple operator-(const tuple& other) const {
    return tuple(p_x - other.p_x, p_y - other.p_y, p_z - other.p_z,
                 p_w - other.p_w);
  }

  tuple operator*(T scalar) const {
    return tuple(p_x * scalar, p_y * scalar, p_z * scalar, p_w * scalar);
  }

  tuple operator/(T scalar) const {
    return tuple(p_x / scalar, p_y / scalar, p_z / scalar, p_w / scalar);
  }

  tuple operator-() const { return *this * -1; }

 private:
  T p_x, p_y, p_z, p_w;
};

using tuple_d = tuple<double>;
using tuple_f = tuple<float>;

}  // namespace raytracer
#endif  // defined TUPLE_H
