#ifndef COLOR_H
#define COLOR_H

#include <raytracer/vec3.h>

namespace raytracer {
class color3 {
 public:
  color3(float red, float green, float blue);

  color3 operator+(const color3& other) const;
  color3 operator-(const color3& other) const;
  color3 operator*(const color3& other) const;

  bool operator==(const color3& other) const;

  float red() const;
  float green() const;
  float blue() const;

 private:
  float p_red, p_green, p_blue;
};

}  // namespace raytracer

#endif
