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

    std::vector<Sphere> m_spheres;
    std::vector<PointLight> m_lights;
};

World default_world()
{
  PointLight light(Point(-10,10,-10), Color(1,1,1));
  Sphere s1;
  Material m1(Color(0.8,1.0,0.6),0.1,0.7,0.2);
  s1.material = m1;
  Sphere s2;
  s2.transform = scaling(0.5,0.5,0.5);
  World w;
  w.m_lights.push_back(light);
  w.m_spheres.push_back(s1);
  w.m_spheres.push_back(s2);

  return w;
}

std::vector<Intersection> intersect_world(World w, Ray r)
{
    std::vector<Intersection> intersections;
    for (auto& sphere: w.m_spheres)
    {
        const auto cur_intersections = sphere.intersect(r);
        std::copy(cur_intersections.begin(), cur_intersections.end(), 
            std::back_inserter(intersections));
    }

    std::sort(intersections.begin(), intersections.end(), [](auto& a, auto& b) {
        return a.t < b.t;
    });

    return intersections;
}

Color shade_hit(World world, Computations comps)
{
    return lighting(comps.m_object->material,
        world.m_lights[0],
        comps.m_point, comps.m_eyev,
        comps.m_normalv);
}


#endif // WORLD_H