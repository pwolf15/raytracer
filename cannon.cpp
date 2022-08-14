#include <iostream>

#include "Environment.h"
#include "Projectile.h"

Projectile tick(Environment e, Projectile p)
{
  Projectile next(p.position + p.velocity, p.velocity + e.gravity + e.wind);
  return next;
}

int main()
{
  std::cout << "Hello cannon!" << std::endl;
  Projectile p(Point(0,1,0), Vector(1,1,0).normalize());
  Environment e(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));

  while (p.position.y > 0)
  {
    p = tick(e, p);
    std::cout << "Position: " << p.position.y << std::endl;
  }
  return 0;
}