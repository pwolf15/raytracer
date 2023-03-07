#ifndef COLOR_H
#define COLOR_H

#include "Tuple.h"

class Color: public Tuple
{
public:
  Color(double r, double g, double b): Tuple(r,g,b,1.0)
  {

  }

  double red() { return x; }
  double green() { return y; }
  double blue() { return z; }
  void red(double r) { x = r; }
  void green(double g) { y = g; }
  void blue(double b) { z = b; }

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

  friend Color operator*(Color lhs, double s)
  {
    Color result(lhs.x * s, lhs.y * s, lhs.z * s);
    return result;
  }


  friend Color operator*(Color lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Color& rhs) // otherwise, both parameters may be const references
  {
    Color result(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
    return result;
  }

};

#endif // COLOR_H