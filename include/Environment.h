#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Vector.h"

class Environment
{
public:
  Environment(Vector wind, Vector gravity): wind(wind), gravity(gravity) {}
  Vector wind;
  Vector gravity;
};

#endif // ENVIRONMENT_H