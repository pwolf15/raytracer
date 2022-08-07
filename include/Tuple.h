#ifndef TUPLE_H
#define TUPLE_H

#include <vector>

class Tuple
{
public:
  Tuple(float x, float y, float z, float w):
    x(x), y(y), z(z), w(w)
  {}

  bool isPoint()
  {
    return w == 1.0;
  }

  bool isVector()
  {
    return w == 0.0;
  }

  bool operator==(Tuple const& rhs) const
  {
    double th = 1e-6;
    bool equal = 
      (abs(x - rhs.x) < th) && 
      (abs(y - rhs.y) < th) &&
      (abs(z - rhs.z) < th) && 
      (abs(w - rhs.w) < th);
    return equal;
  }

  bool operator!=(Tuple const& rhs) const
  {
    return !(*this == rhs);
  }

  friend Tuple operator+(Tuple lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Tuple& rhs) // otherwise, both parameters may be const references
  {
    Tuple result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    return result;
  }

  friend Tuple operator-(Tuple lhs,        // passing lhs by value helps optimize chained a+b+c
                      const Tuple& rhs) // otherwise, both parameters may be const references
  {
    Tuple result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return result;
  }

  float x, y, z, w;

};

#endif