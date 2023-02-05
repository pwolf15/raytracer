#ifndef UTILS_H
#define UTILS_H

#include "Computations.h"
#include "Intersection.h"
#include "Ray.h"
#include "World.h"

std::optional<Intersection> hit(std::vector<Intersection>& xs)
{
    std::vector<Intersection> xs_copy;
    std::copy_if(xs.begin(), xs.end(), std::back_inserter(xs_copy), [](Intersection i) {
        return i.t >= 0;
    });

    std::sort(xs_copy.begin(), xs_copy.end(), [](Intersection a, Intersection b) {
        return a.t < b.t;
    });
    return !xs_copy.empty() ? std::optional<std::reference_wrapper<Intersection>>(xs_copy[0]) : std::nullopt;
}

Computations prepare_computations(Intersection intersection, Ray ray)
{
    float t = intersection.t;
    Sphere* obj = intersection.object;
    Point pos = ray.position(t);
    Vector eyev = -ray.direction, normalv = obj->normal_at(pos);
    bool inside = false;

    // check if intersection occurs on inside of object
    if (normalv.dot(eyev) < 0)
    {
        inside = true;
        normalv = -normalv;
    }
    
    Computations comps(t, obj, pos, eyev, normalv, inside);
    return comps;
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

Color color_at(World world, Ray r)
{
    std::vector<Intersection> intersections = intersect_world(world, r);
    std::optional<Intersection> intersection = hit(intersections);
    
    if (!intersection.has_value())
    {
        return Color(0,0,0);
    }

    std::cout << "HERE!" << std::endl;

    Computations comps = prepare_computations(intersection.value(), r);
    std::cout << "Here2" << std::endl;
    return shade_hit(world, comps);
}


template <class T>
std::vector<Intersection> intersections(std::initializer_list<T> list)
{
    std::vector<Intersection> intersections;
    for (auto elem: list)
    {
        intersections.push_back(elem);
    }

    return intersections;
}

#endif // UTILS_H