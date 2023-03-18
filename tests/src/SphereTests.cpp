#include "CppUTest/CommandLineTestRunner.h"

#include "Sphere.h"
#include "TestUtils.h"
#include "Transformations.h"
#include "Utils.h"
#include "Vector.h"

#define PI 3.1415926535

TEST_GROUP(Spheres)
{

};

TEST(Spheres, Intersect)
{
  Ray r(Point(0,0,-5), Vector(0,0,1));
  std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
  s->set_transform(scaling(2,2,2));

  Matrix inv = s->m_transform.inverse();
  Ray local_ray = r.transform(inv);
  std::vector<Intersection> xs = s->local_intersect(local_ray);
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(3, xs[0].t, 0);
  DOUBLES_EQUAL(7, xs[1].t, 0);

  s->set_transform(translation(5,0,0));
  inv = s->m_transform.inverse();
  local_ray = r.transform(inv);
  xs = s->local_intersect(local_ray);
  CHECK_EQUAL(0, xs.size());
}

TEST(Spheres, NormalAt)
{
  Sphere s;
  Vector n = s.normal_at(Point(1,0,0));
  CHECK(Vector(1,0,0) == n);
  n = s.normal_at(Point(0,1,0));
  CHECK(Vector(0,1,0) == n);
  n = s.normal_at(Point(0,0,1));
  CHECK(Vector(0,0,1) == n);
  n = s.normal_at(Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  CHECK(Vector(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3) == n.normalize());

  // translated
  s.set_transform(translation(0,1,0));
  n = s.normal_at(Point(0,1.70711,-0.70711));
  TUPLES_EQUAL(Vector(0,0.70711,-0.70711), n, 1e-5);

  // transformed
  s.set_transform(scaling(1,0.5,1)*rotation_z(PI/5));
  n = s.normal_at(Point(0, sqrt(2)/2,-sqrt(2)/2));
  TUPLES_EQUAL(Vector(0,0.97014,-0.24254), n, 1e-5);
}