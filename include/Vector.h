#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#include "Tuple.h"


class Vector: public Tuple
{
public:
  Vector()=default;
  Vector(const Tuple& a) : Tuple(a) {}
  Vector(double x, double y, double z): Tuple(x, y, z, 0.0)
  {}
  double magnitude() const
  {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  }
  Vector normalize() const
  {
    double mag = this->magnitude();
    Vector v(this->x/mag, this->y/mag,this->z/mag);
    return v;
  }
  double dot(const Tuple& rhs) const
  {
    return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z + this->w*rhs.w;
  }
  Vector cross(const Tuple& rhs) const
  {
    return Vector(this->y*rhs.z - this->z*rhs.y, 
      this->z*rhs.x - this->x*rhs.z, 
      this->x*rhs.y-this->y*rhs.x);
  }

  Vector reflect(Vector normal)
  {
    Vector in = (*this);
    return in - normal * 2 * in.dot(normal);
  }
};

#endif