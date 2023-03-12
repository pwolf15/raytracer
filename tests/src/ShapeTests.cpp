#include "CppUTest/CommandLineTestRunner.h"

#include "Shape.h"
#include "TestShape.h"
#include "Transformations.h"

TEST_GROUP(Shape)
{

};

TEST(Shape, Transform)
{
    // Shape s1; // compile error due to abstract class
    TestShape s;
    Matrix identity(
    {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
    CHECK(identity == s.m_transform);

    Matrix t = translation(2, 3, 4);
    s.set_transform(t);
    CHECK(s.m_transform == t);
}

TEST(Shape, Material)
{
  TestShape s;
  Material m;
  CHECK(Material() == s.m_material);

  m.ambient = 1;
  s.m_material = m;
  CHECK(m == s.m_material);
}