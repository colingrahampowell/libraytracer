#ifndef VEC3_H
#define VEC3_H

#include <raytracer/math_tools.h>

#include <cmath>
#include <type_traits>

namespace raytracer {

template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
class vec3 {
 public:
  vec3(T x, T y, T z) : p_x(x), p_y(y), p_z(z) {}

  T x() const { return p_x; }
  T y() const { return p_y; }
  T z() const { return p_z; }

  // Comparison
  bool operator==(const vec3& other) const {
    if (about_equal(p_x, other.p_x) && about_equal(p_y, other.p_y) &&
        about_equal(p_z, other.p_z)) {
      return true;
    }
    return false;
  }

  // Arithmetic operators:
  vec3 operator+(const vec3& other) const {
    return vec3(p_x + other.p_x, p_y + other.p_y, p_z + other.p_z);
  }

  vec3 operator-(const vec3& other) const {
    return vec3(p_x - other.p_x, p_y - other.p_y, p_z - other.p_z);
  }

  vec3 operator*(T scalar) const {
    return vec3(p_x * scalar, p_y * scalar, p_z * scalar);
  }

  vec3 operator/(T scalar) const {
    return vec3(p_x / scalar, p_y / scalar, p_z / scalar);
  }

  vec3 operator-() const { return *this * -1; }

  T magnitude() const { return std::sqrt(p_x * p_x + p_y * p_y + p_z * p_z); }

  vec3 normalize() const {
    const auto mag = this->magnitude();
    return vec3(p_x / mag, p_y / mag, p_z / mag);
  }

  T dot(const vec3& other) const {
    return p_x * other.p_x + p_y * other.p_y + p_z * other.p_z;
  }

  vec3 cross(const vec3& other) const {
    return vec3((p_y * other.p_z - p_z * other.p_y),
                (p_z * other.p_x - p_x * other.p_z),
                (p_x * other.p_y - p_y * other.p_x));
  }

 private:
  T p_x, p_y, p_z;
};

using vec3d = vec3<double>;
using vec3f = vec3<float>;

}  // namespace raytracer
#endif  
