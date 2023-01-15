#include <iostream>

#include "Canvas.h"
#include "Ray.h"
#include "Sphere.h"
#include "Transformations.h"
#include "PointLight.h"
#include "Lighting.h"

int main()
{
    Point eye_origin(0,0,-5);

    int canvas_width = 100;
    int canvas_height = 100;
    float wall_z = 10;
    float wall_size = 7.0;
    float pixel_size = wall_size / canvas_width;
    float half = wall_size / 2;

    Canvas c(500, 500);

    Sphere s;
    s.material.color = Color(1,0.2,1);
    s.material.ambient = 0.1;
    s.material.diffuse = 0.9;
    s.material.specular = 0.9;
    s.material.shininess = 200.0;

    PointLight light(Color(1,1,1), Point(-10,10,-10));

    // some experiments

    // shrink along y
    // s.set_transform(scaling(1, 0.5, 1));
    // shrink along x
    // s.set_transform(scaling(0.5,1,1));
    // shrink and rotate
    // const float PI = 3.1415926535;
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
            std::vector<Intersection> intersections = s.intersect(r);
            std::optional<Intersection> hitPoint = hit(intersections);
            if (hitPoint.has_value())
            {
                Point p = r.position(hitPoint->t); // retreive point of interesection
                Vector normal = hitPoint->object->normal_at(p);
                Color color = lighting(hitPoint->object->material, light, p, eyev, normal);
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