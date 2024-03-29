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

TEST_GROUP(Material)
{

};

TEST(Material, Material)
{
  Material m(Color(1,1,1), 0.1, 0.9, 0.9, 200.0);
  CHECK(Color(1,1,1) == m.color);
  DOUBLES_EQUAL(0.1, m.ambient, 1e-3);
  DOUBLES_EQUAL(0.9, m.diffuse, 1e-3);
  DOUBLES_EQUAL(0.9, m.specular, 1e-3);
  DOUBLES_EQUAL(200, m.shininess, 1e-3);
  DOUBLES_EQUAL(0.1, m.ambient, 1e-3);
}

TEST(Material, Phong)
{
  Material m;
  m.ambient = 0.1;
  m.diffuse = 0.9;
  m.specular = 0.9;
  m.shininess = 200.0;
  m.color = Color(1,1,1);
  Point position(0,0,0);
  Vector eyev(0,0,-1), normalv(0,0,-1);
  PointLight light(Point(0,0,-10), Color(1,1,1));
  Color result = lighting(m, light, position, eyev, normalv);
  std::cout << "Result: " << result << std::endl;
  CHECK(Color(1.9,1.9,1.9) == result);

  eyev = Vector(0,sqrt(2)/2,-sqrt(2)/2);
  result = lighting(m, light, position, eyev, normalv);
  CHECK(Color(1.0,1.0,1.0) == result);
  
  eyev = Vector(0,0,-1);
  light = PointLight(Point(0,10,-10), Color(1,1,1));
  result = lighting(m, light, position, eyev, normalv);
  CHECK(Color(0.7364,0.7364,0.7364) == result);

  eyev = Vector(0,-sqrt(2)/2,-sqrt(2)/2);
  normalv = Vector(0,0,-1);
  light = PointLight(Point(0,10,-10), Color(1,1,1));
  result = lighting(m, light, position, eyev, normalv);
  TUPLES_EQUAL(Color(1.6364,1.6364,1.6364), result);

  eyev = Vector(0,0,-1);
  normalv = Vector(0,0,-1);
  light = PointLight(Point(0,0,10), Color(1,1,1));
  result = lighting(m, light, position, eyev, normalv);
  TUPLES_EQUAL(Color(0.1,0.1,0.1), result);

  // in shadow
  eyev = Vector(0,0,-1);
  normalv = Vector(0,0,-1);
  light = PointLight(Point(0,0,-10), Color(1,1,1));
  bool in_shadow = true;
  result = lighting(m, light, position, eyev, normalv, in_shadow);
  TUPLES_EQUAL(Color(0.1,0.1,0.1), result);
} 

TEST(Material, Pattern)
{
  // Lighting with a pattern applied
  Material m;
  Color white(1,1,1);
  Color black(0,0,0);
  m.pattern = stripe_pattern(white, black);
  m.ambient = 1;
  m.diffuse = 0;
  m.specular = 0;
  Vector eyev(0,0,-1);
  Vector normalv(0,0,-1);
  PointLight light(Point(0,0,-10),Color(1,1,1));
  Color c1 = lighting(m, light, Point(0.9,0,0), eyev, normalv, false);
  Color c2 = lighting(m, light, Point(1.1,0,0), eyev, normalv, false);
  CHECK(white == c1);
  CHECK(black == c2);
}