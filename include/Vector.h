#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#include "Tuple.h"


class Vector: public Tuple
{
public:
  Vector()=default;
  Vector(const Tuple& a) : Tuple(a) {}
  Vector(float x, float y, float z): Tuple(x, y, z, 0.0)
  {}
  float magnitude() const
  {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  }
  Vector normalize() const
  {
    float mag = this->magnitude();
    Vector v(this->x/mag, this->y/mag,this->z/mag);
    return v;
  }
  float dot() const
  {
    return 0.0;
  }
};

#endif