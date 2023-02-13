#include "CppUTest/CommandLineTestRunner.h"

#include "Camera.h"

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