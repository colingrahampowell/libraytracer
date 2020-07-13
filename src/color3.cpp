
#include <raytracer/color3.h>
#include <raytracer/math_tools.h>

namespace raytracer {

color3::color3(float red, float green, float blue)
    : p_red(red), p_green(green), p_blue(blue) {}

color3 color3::operator+(const color3& other) const {
  return color3(p_red + other.p_red, p_green + other.p_green,
                p_blue + other.p_blue);
}

color3 color3::operator-(const color3& other) const {
  return color3(p_red - other.p_red, p_green - other.p_green,
                p_blue - other.p_blue);
}

color3 color3::operator*(const color3& other) const {
  // Hadamard / Schur product
  return color3(p_red * other.p_red, p_green * other.p_green,
                p_blue * other.p_blue);
}

bool color3::operator==(const color3& other) const {
  return (about_equal(p_red, other.p_red) &&
          about_equal(p_green, other.p_green) &&
          about_equal(p_blue, other.p_blue));
}

float color3::red() const { return p_red; }
float color3::green() const { return p_green; };
float color3::blue() const { return p_blue; };

}  // namespace raytracer
