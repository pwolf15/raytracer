#ifndef UTILS_H
#define UTILS_H

#include "Camera.h"
#include "Canvas.h"
#include "Computations.h"
#include "Lighting.h"
#include "Transformations.h"
#include "Intersection.h"
#include "Ray.h"
#include "TestShape.h"
#include "World.h"
#include "Pattern.h"

inline static Color stripe_at(Pattern pattern, Point point)
{
    return (int)(floor(point.x)) % 2 == 0 ? pattern.m_a : pattern.m_b;
}

inline static Color stripe_at_object(Pattern pattern, std::shared_ptr<Shape> shape, Point world_point)
{
    Point object_point = shape->m_transform.inverse() * world_point;
    Point pattern_point = pattern.m_transform.inverse() * object_point;

    return stripe_at(pattern, pattern_point);
}

inline static bool has_pattern(const Material& mat)
{
    return mat.pattern.m_a != mat.pattern.m_b;
}

static inline Color lighting(Material material, PointLight light, Point point, Vector eyev, Vector normalv, bool in_shadow = false)
{
    Color material_color(0,0,0);
    if (has_pattern(material))
    {
        material_color = stripe_at(material.pattern, point);
    }
    else
    {
        material_color = material.color;
    }
    Color effective_color = material_color * light.intensity;
    // std::cout << "Color: " << material.color << std::endl;
    // std::cout << "Intensity: " << light.intensity << std::endl;
    // std::cout << "Effective color: " << effective_color << std::endl;
    Vector lightv = Vector(light.position - point).normalize();

    Color ambient = effective_color * material.ambient;
    Color diffuse(0.0, 0.0, 0.0), specular(0.0,0.0,0.0);

    double light_dot_normal = lightv.dot(normalv);
    if (light_dot_normal < 0)
    {
        diffuse = Color(0.0,0.0,0.0);
        specular = Color(0.0,0.0,0.0);
    }
    else
    {
        diffuse = effective_color * material.diffuse * light_dot_normal;
        Vector reflectv = ((Vector)-lightv).reflect(normalv);
        double reflect_dot_eye = reflectv.dot(eyev);
        if (reflect_dot_eye <= 0)
        {
            specular = Color(0.0,0.0,0.0);
        }
        else
        {
            double factor = pow(reflect_dot_eye, material.shininess);
            // std::cout << "reflect_dot_eye: " << reflect_dot_eye << std::endl;
            // std::cout << "shininess" << material.shininess << std::endl;
            // std::cout << "Factor: " << factor << std::endl;
            // std::cout << "Maetiral specular: " << material.specular << std::endl;
            // std::cout << "Light intesnity: " << light.intensity << std::endl;
            specular = light.intensity * material.specular * factor;
        }
    }

    // std::cout << "Ambient: " << ambient <<std::endl;
    // std::cout << "Diffuse: " << diffuse << std::endl;
    // std::cout << "Specular: " << specular << std::endl;

    if (in_shadow)
    {
        specular = Color(0, 0, 0);
        diffuse = Color(0, 0, 0);
    }

    return ambient + diffuse + specular;
}

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

inline static Vector normal_at(std::shared_ptr<Shape> shape, Point point)
{
    Point local_point = shape->m_transform.inverse() * point;
    Vector local_normal = shape->normal_at(local_point);
    Vector world_normal = shape->m_transform.inverse().transpose() * local_normal;
    world_normal.w = 0;

    return world_normal.normalize();
}

inline static Computations prepare_computations(Intersection intersection, Ray ray)
{
    double t = intersection.t;
    std::shared_ptr<Shape> obj = intersection.object;
    Point pos = ray.position(t);
    Vector eyev = -ray.direction, normalv = obj->normal_at(pos);
    bool inside = false;

    // check if intersection occurs on inside of object
    if (normalv.dot(eyev) < 0)
    {
        inside = true;
        normalv = -normalv;
    }
    
    Point over_point = pos + normalv * EPSILON;
    Computations comps(t, obj, pos, over_point, eyev, normalv, inside);
    return comps;
}

inline static std::vector<Intersection> intersect(std::shared_ptr<Shape> s, Ray r)
{
    Matrix inv = s->m_transform.inverse();
    Ray local_ray = r.transform(inv);
    return s->local_intersect(local_ray);
}

inline static std::vector<Intersection> intersect_world(World w, Ray r)
{
    std::vector<Intersection> intersections;
    for (auto& shape: w.m_shapes)
    {
        const auto cur_intersections = intersect(shape, r);
        std::copy(cur_intersections.begin(), cur_intersections.end(), 
            std::back_inserter(intersections));
    }

    std::sort(intersections.begin(), intersections.end(), [](auto& a, auto& b) {
        return a.t < b.t;
    });

    return intersections;
}

inline static bool is_shadowed(World world, Point p)
{
    Point lightPosition = world.m_lights[0].position;
    Vector v = lightPosition - p;
    double distance = v.magnitude();
    Vector direction = v.normalize();
    Ray r(p, direction);
    std::vector<Intersection> intersections = intersect_world(world, r);

    std::optional<Intersection> h = hit(intersections);
    if (h.has_value() && h.value().t < distance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline static Color shade_hit(World world, Computations comps)
{
    bool shadowed = is_shadowed(world, comps.m_over_point);
    return lighting(comps.m_object->m_material,
        world.m_lights[0],
        comps.m_over_point, comps.m_eyev,
        comps.m_normalv,
        shadowed);
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
    double xoffset = (px + 0.5) * camera.m_pixel_size;
    double yoffset = (py + 0.5) * camera.m_pixel_size;

    double world_x = camera.m_half_width - xoffset;
    double world_y = camera.m_half_height - yoffset;
    Point pixel = camera.m_transform.inverse() * Point(world_x, world_y, -1);
    Vector origin = camera.m_transform.inverse() * Point(0,0,0);
    Vector direction = Vector(pixel.x - origin.x, pixel.y - origin.y, pixel.z - origin.z).normalize();

    return Ray(origin, direction);
}

inline static Canvas render(Camera camera, World world)
{
    Canvas image(camera.m_hsize, camera.m_vsize);

    for (int y = 0; y < camera.m_vsize; ++y)
    {
        for (int x = 0; x < camera.m_hsize; ++x)
        {
            Ray ray = ray_for_pixel(camera, x, y);
            Color color = color_at(world, ray);
            image.write_pixel(x, y, color);
        }
    }
    
    return image;
}

inline static Pattern stripe_pattern(Color a, Color b)
{
    Pattern p;
    p.m_a = a;
    p.m_b = b;
    return p;
}

#endif // UTILS_H