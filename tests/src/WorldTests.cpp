#include <iostream>

#include "CppUTest/CommandLineTestRunner.h"

#include "Color.h"
#include "Lighting.h"
#include "Material.h"
#include "Point.h"
#include "PointLight.h"
#include "TestUtils.h"
#include "Utils.h"
#include "Vector.h"
#include "World.h"

TEST_GROUP(World)
{

};

TEST(World, World)
{
  World w;
  CHECK(w.m_shapes.empty());
  CHECK(w.m_lights.empty());

  PointLight light(Point(-10,10,-10), Color(1,1,1));
  
  std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>();
  Material m1(Color(0.8,1.0,0.6),0.1,0.7,0.2);
  s1->m_material = m1;
  std::shared_ptr<Sphere> s2 = std::make_shared<Sphere>();
  s2->m_transform = scaling(0.5,0.5,0.5);

  w = default_world();

  // lights
  CHECK_EQUAL(1, w.m_lights.size());
  CHECK(light == w.m_lights[0]);

  // objects
  CHECK_EQUAL(2, w.m_shapes.size());
  CHECK(*std::dynamic_pointer_cast<Sphere>(w.m_shapes[0]) == *s1);
  CHECK(*std::dynamic_pointer_cast<Sphere>(w.m_shapes[1]) == *s2);
}

TEST(World, IntersectWorld)
{
  World w = default_world();
  Ray r(Point(0,0,-5),Vector(0,0,1));
  std::vector<Intersection> xs = intersect_world(w, r);
  CHECK_EQUAL(4, xs.size());
  DOUBLES_EQUAL(4, xs[0].t, 0);
  DOUBLES_EQUAL(4.5, xs[1].t, 0);
  DOUBLES_EQUAL(5.5, xs[2].t, 0);
  DOUBLES_EQUAL(6, xs[3].t, 0);
}

TEST(World, ShadeHit)
{
  World w = default_world();
  Ray r(Point(0,0,-5), Vector(0,0,1));
  std::shared_ptr<Sphere> shape = std::dynamic_pointer_cast<Sphere>(w.m_shapes[0]);
  Intersection i(4, shape);
  Computations comps = prepare_computations(i, r);
  Color c = shade_hit(w, comps);

  CHECK(Color(0.38066,0.47583,0.2855) == c);

  w.m_lights[0] = PointLight(Point(0,0.25,0),Color(1,1,1));
  r = Ray(Point(0,0,0), Vector(0,0,1));
  shape = std::dynamic_pointer_cast<Sphere>(w.m_shapes[1]);
  Intersection i2(0.5, shape);
  comps = prepare_computations(i2, r);
  c = shade_hit(w, comps);
  
  CHECK(Color(0.90498,0.90498,0.90498) == c);

  w.m_lights[0] = PointLight(Point(0, 0, -10), Color(1,1,1));
  w.m_shapes[0] = std::make_shared<Sphere>();
  w.m_shapes[1] = std::make_shared<Sphere>();
  w.m_shapes[1]->m_transform = translation(0, 0, 10);
  r = Ray(Point(0, 0, 5), Vector(0,0,1));
  i = Intersection(4, w.m_shapes[1]);
  comps = prepare_computations(i, r);
  c = shade_hit(w, comps);
  CHECK(Color(0.1,0.1,0.1) == c);
}

TEST(World, ColorAt)
{
  World w = default_world();
  Ray r(Point(0,0,-5),Vector(0,1,0));
  Color c = color_at(w, r);
  CHECK(Color(0,0,0) == c);

  r = Ray(Point(0,0,-5), Vector(0,0,1));
  c = color_at(w, r);
  CHECK(Color(0.38066,0.47583,0.2855) == c);

  std::shared_ptr<Sphere> outer = std::dynamic_pointer_cast<Sphere>(w.m_shapes[0]);
  outer->m_material.ambient = 1;
  std::shared_ptr<Sphere> inner = std::dynamic_pointer_cast<Sphere>(w.m_shapes[1]);
  inner->m_material.ambient = 1;
  r = Ray(Point(0,0,0.75), Vector(0,0,-1));
  c = color_at(w, r);
  CHECK(inner->m_material.color == c);
}

TEST(World, IsShadowed)
{
    World w = default_world();
    Point p(0, 10, 0);
    CHECK(!is_shadowed(w, p));

    p = Point(10,-10,10);
    CHECK(is_shadowed(w, p));
    
    p = Point(-20, 20, -20);
    CHECK(!is_shadowed(w, p));

    p = Point(-2, 2, -2);
    CHECK(!is_shadowed(w, p));
}