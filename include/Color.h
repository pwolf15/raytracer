#ifndef COLOR_H
#define COLOR_H

#include "Tuple.h"

class Color: public Tuple
{
public:
  Color(float r, float g, float b): Tuple(r,g,b,1.0)
  {

  }

  float red() { return x; }
  float green() { return y; }
  float blue() { return z; }
  void red(float r) { x = r; }
  void green(float g) { y = g; }
  void blue(float b) { z = b; }

  friend Color operator+(Color lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Color& rhs) // otherwise, both parameters may be const references
  {
    Color result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    return result;
  }

  friend Color operator-(Color lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Color& rhs) // otherwise, both parameters may be const references
  {
    Color result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return result;
  }

  friend Color operator*(Color lhs, float s)
  {
    Color result(lhs.x * s, lhs.y * s, lhs.z * s);
    return result;
  }
};

#endif // COLOR_H