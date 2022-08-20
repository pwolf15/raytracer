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
};

#endif // COLOR_H