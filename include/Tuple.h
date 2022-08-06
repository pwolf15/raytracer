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

  float x, y, z, w;

};

#endif