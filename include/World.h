#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Computations.h"
#include "Intersection.h"
#include "Sphere.h"
#include "PointLight.h"

class World
{
public:
    World() {}

    std::vector<std::shared_ptr<Sphere>> m_spheres;
    std::vector<PointLight> m_lights;
};

World default_world()
{
  PointLight light(Point(-10,10,-10), Color(1,1,1));
  std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>();
  Material m1(Color(0.8,1.0,0.6),0.1,0.7,0.2);
  s1->material = m1;
  std::shared_ptr<Sphere> s2 = std::make_shared<Sphere>();
  s2->transform = scaling(0.5,0.5,0.5);
  World w;
  w.m_lights.push_back(light);
  w.m_spheres.push_back(s1);
  w.m_spheres.push_back(s2);

  return w;
}

#endif // WORLD_H