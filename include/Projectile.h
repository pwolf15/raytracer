#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Point.h"
#include "Vector.h"

class Projectile 
{
public:
  Projectile(Point position, Vector velocity): position(position), velocity(velocity) {}
  Point position;
  Vector velocity;

private:
};

#endif // PROJECTILE_H