#include <math.h>
#include <fstream>
#include <iostream>
#include "Canvas.h"
#include "Point.h"
#include "Transformations.h"

#define PI 3.14159265
int main()
{
    Canvas c(600, 600);

    c.write_pixel(c.width / 2, c.height / 2, Color(1.0, 0.0,0.0));

    int w = c.width;
    int h = c.height;

    Point center({0, 0, 0});

    std::vector<Point> points;

    // new center
    Point newCenter = translation(w/2, h/2, 0) * center;
    points.push_back(newCenter);

    // assuming top at 0,1
    // to map to canvas coordinates: 
    // 1. reflect about (x-axis); top in canvas coordinates at w/2, 0
    // 2. scale by radius of clock: just assume square canvas
    // 3. translate point to canvas coords (no negative coordinates)

    Point top = translation(0, 1, 0) * center;
    Matrix worldT = translation(w/2, h/2, 0) * scaling(w/4, h/4, 1) * scaling(1, -1, 1);
    Point newTop = worldT * top;

    // creates 12 evenly spaced points along circumference
    // 2*PI/12 represents distance between two points
    // each point is top point, rotated by PI/6

    double start = 0;
    const int numPoints = 12;
    const double circum = 2 * PI;
    constexpr double rad = 2*PI/numPoints;
    for (int i = 0; i < numPoints; ++i)
    {
        Matrix newPointT = worldT * rotation_z(start);
        Point worldPoint = newPointT * top;
        points.push_back(worldPoint);
        start += rad;
    }
    
    points.push_back(newTop);

    for (auto& point: points)
    {
        c.write_pixel(point.x, point.y, Color(1.0, 0.0,0.0));
    }
    std::string ppm = c.canvas_to_ppm();
    std::ofstream f("clock.ppm");
    f << ppm;
    f.close();
}