#include <iostream>

#include "Canvas.h"
#include "Ray.h"
#include "Sphere.h"
#include "Transformations.h"
#include "PointLight.h"
#include "Lighting.h"
#include "Utils.h"

int main()
{
    Point eye_origin(0,0,-5);

    int canvas_width = 200;
    int canvas_height = 200;
    double wall_z = 10;
    double wall_size = 7.0;
    double pixel_size = wall_size / canvas_width;
    double half = wall_size / 2;

    Canvas c(canvas_width, canvas_height);

    std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
    s->m_material.color = Color(1,0.2,1);
    s->m_material.ambient = 0.1;
    s->m_material.diffuse = 0.9;
    s->m_material.specular = 0.9;
    s->m_material.shininess = 200.0;

    PointLight light(Point(-10,10,-10), Color(1,1,1));

    // some experiments

    // shrink along y
    // s.set_transform(scaling(1, 0.5, 1));
    // shrink along x
    // s.set_transform(scaling(0.5,1,1));
    // shrink and rotate
    // const double PI = 3.1415926535;
    // s.set_transform(rotation_z(PI/4) * scaling(0.5,1,1));
    // shrink and skew it
    // s.set_transform(shearing(1,0,0,0,0,0)*scaling(0.5,1,1));

    int numHits = 0;

    for (int i = 0; i < canvas_height; ++i)
    {
        for (int j = 0; j < canvas_width; ++j)
        {
            // for each canvas pixel, cast ray to relative point on wall
            // note, for y, greater i corresponds to lesser y in coord space
            // for this reason, we subtract from half (largest wall y coord)
            Point wallPoint(j*pixel_size-half, half-i*pixel_size, wall_z);
            Vector eyev = Vector(wallPoint-eye_origin).normalize();
            Ray r(eye_origin, eyev);
        
            // obtain intersections for given ray
            // if hit occurs, update the pixel color
            std::vector<Intersection> intersections = intersect(s,r);
            std::optional<Intersection> hitPoint = hit(intersections);
            if (hitPoint.has_value())
            {
                Point p = r.position(hitPoint->t); // retreive point of interesection
                Vector normal = hitPoint->object->normal_at(p);
                Color color = lighting(hitPoint->object->m_material, light, p, -eyev, normal);
                c.write_pixel(i, j, color);
                numHits++;
            }
        }
    }

    std::string ppm = c.canvas_to_ppm();
    std::ofstream f("sphere2d.ppm");
    f << ppm;
    f.close();

    std::cout << "Num hits: " << numHits << std::endl; 

    return 0;
}