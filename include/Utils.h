#ifndef UTILS_H
#define UTILS_H

#include "Camera.h"
#include "Computations.h"
#include "Lighting.h"
#include "Transformations.h"
#include "Intersection.h"
#include "Ray.h"
#include "World.h"

inline static std::optional<Intersection> hit(std::vector<Intersection>& xs)
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

inline static Computations prepare_computations(Intersection intersection, Ray ray)
{
    float t = intersection.t;
    std::shared_ptr<Sphere> obj = intersection.object;
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

inline static std::vector<Intersection> intersect(std::shared_ptr<Sphere> s, Ray r)
{
    std::vector<Intersection> ts;

    Matrix inv = s->transform.inverse();
    Ray ray2 = r.transform(inv);
    Vector sphere_to_ray = ray2.origin - Point(0, 0, 0);
    float a = ray2.direction.dot(ray2.direction);
    float b = 2 * ray2.direction.dot(sphere_to_ray);
    float c = sphere_to_ray.dot(sphere_to_ray) - 1;
    float discriminant = pow(b,2) - 4*a*c;

    if (discriminant < 0)
    {
        return ts;
    }

    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    ts.push_back(Intersection(t1, s));
    ts.push_back(Intersection(t2, s));
    
    return ts;
}

inline static std::vector<Intersection> intersect_world(World w, Ray r)
{
    std::vector<Intersection> intersections;
    for (auto& sphere: w.m_spheres)
    {
        const auto cur_intersections = intersect(sphere, r);
        std::copy(cur_intersections.begin(), cur_intersections.end(), 
            std::back_inserter(intersections));
    }

    std::sort(intersections.begin(), intersections.end(), [](auto& a, auto& b) {
        return a.t < b.t;
    });

    return intersections;
}

inline static Color shade_hit(World world, Computations comps)
{
    return lighting(comps.m_object->material,
        world.m_lights[0],
        comps.m_point, comps.m_eyev,
        comps.m_normalv);
}

inline static Color color_at(World world, Ray r)
{
    std::vector<Intersection> intersections = intersect_world(world, r);
    std::optional<Intersection> intersection = hit(intersections);

    if (!intersection.has_value())
    {
        return Color(0,0,0);
    }
    Computations comps = prepare_computations(intersection.value(), r);
    return shade_hit(world, comps);
}


template <class T>
inline static std::vector<Intersection> intersections(std::initializer_list<T> list)
{
    std::vector<Intersection> intersections;
    for (auto elem: list)
    {
        intersections.push_back(elem);
    }

    return intersections;
}

inline static Ray ray_for_pixel(Camera camera, int px, int py)
{
    float xoffset = (px + 0.5) * camera.m_pixel_size;
    float yoffset = (py + 0.5) * camera.m_pixel_size;

    float world_x = camera.m_half_width - xoffset;
    float world_y = camera.m_half_height - yoffset;
    Point pixel = camera.m_transform.inverse() * Point(world_x, world_y, -1);
    Vector origin = camera.m_transform.inverse() * Point(0,0,0);
    Vector direction = Vector(pixel.x - origin.x, pixel.y - origin.y, pixel.z - origin.z).normalize();

    return Ray(origin, direction);
}


#endif // UTILS_H