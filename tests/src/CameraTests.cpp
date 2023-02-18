#include "CppUTest/CommandLineTestRunner.h"

#include "Camera.h"
#include "Utils.h"

#define PI 3.1415926535

TEST_GROUP(Camera)
{

};

TEST(Camera, Camera)
{
    Camera c(160, 120, PI/2);
    double th = 1e-6;
    LONGS_EQUAL(160, c.m_hsize);
    LONGS_EQUAL(120, c.m_vsize);
    DOUBLES_EQUAL(PI/2, c.m_field_of_view, th);
    Matrix i({
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
    CHECK(i == c.m_transform);

    Camera c2(200, 125, PI/2);
    DOUBLES_EQUAL(0.01, c2.m_pixel_size, th);

    Camera c3(125, 200, PI/2);
    DOUBLES_EQUAL(0.01, c2.m_pixel_size, th);
}

TEST(Camera, RayForPixel)
{
    Camera c(201, 101, PI/2);
    Ray r = ray_for_pixel(c, 100, 50);
    CHECK(Point(0,0,0) == r.origin);
    CHECK(Vector(0,0,-1) == r.direction);

    r = ray_for_pixel(c, 0, 0);
    CHECK(Point(0,0,0) == r.origin);
    CHECK(Vector(0.66519,0.33259,-0.66851) == r.direction);

    c.m_transform = rotation_y(PI/4) * translation(0, -2, 5);
    r = ray_for_pixel(c, 100, 50);
    CHECK(Point(0,2,-5) == r.origin);
    CHECK(Vector(sqrt(2)/2,0,-sqrt(2)/2) == r.direction);  
}

TEST(Camera, Render)
{
    World w = default_world();
    Camera c(11, 11, PI/2);
    Point from(0, 0, -5);
    Point to(0,0,0);
    Vector up(0,1,0);
    c.m_transform = view_transform(from, to, up);
    Canvas image = render(c, w);
    CHECK(Color(0.38066,0.47583,0.2855) == image.pixel_at(5,5));
}