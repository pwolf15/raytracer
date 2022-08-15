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
  Projectile p(Point(0,1,0), Vector(5,5,0).normalize());
  Environment e(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));

  int tickNum = 0;
  while (p.position.y > 0)
  {
    p = tick(e, p);
    tickNum++;
    std::cout << "Tick #" << tickNum << ": (" << p.position.x << "," << p.position.y << "," << p.position.z << ")" << std::endl;
  }
  return 0;
}