#include <iostream>

#include "Canvas.h"
#include "Ray.h"
#include "Sphere.h"

int main()
{
    Point eye_origin(0,0,-5);

    int canvas_width = 100;
    int canvas_height = 100;
    float wall_z = 10;
    float wall_size = 7.0;
    float pixel_size = wall_size / canvas_width;
    float half = wall_size / 2;

    Canvas c(100, 100);

    Sphere s;

    int numHits = 0;

    for (int i = 0; i < canvas_height; ++i)
    {
        for (int j = 0; j < canvas_width; ++j)
        {
            // for each canvas pixel, cast ray to relative point on wall
            // note, for y, greater i corresponds to lesser y in coord space
            // for this reason, we subtract from half (largest wall y coord)
            Point wallPoint(j*pixel_size-half, half-i*pixel_size, wall_z);
            Ray r(eye_origin, Vector(wallPoint.x-eye_origin.x, wallPoint.y-eye_origin.y, wallPoint.z-eye_origin.z));
        
            // obtain intersections for given ray
            // if hit occurs, update the pixel color
            std::vector<Intersection> intersections = s.intersect(r);
            std::optional<Intersection> hitPoint = hit(intersections);
            if (hitPoint.has_value())
            {
                c.write_pixel(i, j, Color(1.0,0.0,0.0));
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