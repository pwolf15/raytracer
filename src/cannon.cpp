#include <math.h>
#include <fstream>
#include <iostream>
#include "Canvas.h"
#include "Environment.h"
#include "Projectile.h"

Projectile tick(Environment e, Projectile p)
{
  Projectile next(p.position + p.velocity, p.velocity + e.gravity + e.wind);
  return next;
}

int main()
{
  Projectile p(Point(0,1,0), Vector(1, 1.8,0).normalize() * 11.25);
  Environment e(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));

  Canvas c(900, 550);
  int tickNum = 0;
  while (p.position.y > 0)
  {
    p = tick(e, p);
    tickNum++;
    std::cout << "Tick #" << tickNum << ": (" << p.position.x << "," << p.position.y << "," << p.position.z << ")" << std::endl;
    c.write_pixel(c.width - p.position.x, c.height - p.position.y, Color(1.0,0.0,0.0));
  }
  std::string ppm = c.canvas_to_ppm();
  std::ofstream f("cannon.ppm");
  f << ppm;
  f.close();
  
  return 0;
}