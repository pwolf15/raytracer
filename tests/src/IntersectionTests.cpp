#include "CppUTest/CommandLineTestRunner.h"

#include "Tuple.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Transformations.h"
#include "Ray.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Material.h"
#include "Lighting.h"
#include "World.h"
#include "Computations.h"
#include "TestUtils.h"
#include "Utils.h"

TEST_GROUP(Intersection)
{

};

TEST(Intersection, Intersection)
{
  std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
  Intersection i(3.5, s);

  DOUBLES_EQUAL(3.5, i.t, 0);
  CHECK(*s == *((Sphere*)(i.object.get())));
}

TEST(Intersection, Intersections)
{
  std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
  Intersection i1(1, s), i2(2, s);
  std::vector<Intersection> xs = intersections({i1, i2});
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(1, xs[0].t, 0);
  DOUBLES_EQUAL(2, xs[1].t, 0);
}

TEST(Intersection, Hit)
{
  std::shared_ptr<Sphere> s = std::make_shared<Sphere>();
  Intersection i1(1, s), i2(2, s);
  std::vector<Intersection> xs = intersections({i1, i2});
  std::optional<Intersection> i_opt = hit(xs);
  CHECK(i_opt.has_value());
  CHECK_EQUAL(i1.t, i_opt->t);

  Intersection i3(-1, s), i4(1, s);
  xs = intersections({i3, i4});
  i_opt = hit(xs);
  CHECK(i_opt.has_value());
  CHECK_EQUAL(i4.t, i_opt->t);

  Intersection i5(-2, s), i6(-1, s);
  xs = intersections({i5, i6});
  i_opt = hit(xs);
  CHECK(!i_opt.has_value());

  Intersection i7(5, s), i8(7, s), i9(-3, s), i10(2, s);
  xs = intersections({i7,i8,i9,i10});
  i_opt = hit(xs);
  CHECK(i_opt.has_value());
  CHECK_EQUAL(i10.t, i_opt->t);
}

TEST(Intersection, Computations)
{
  Ray r(Point(0, 0, -5), Vector(0,0,1));
  std::shared_ptr<Sphere> shape = std::make_shared<Sphere>();
  Intersection i(4, shape);

  Computations comps = prepare_computations(i, r);
  DOUBLES_EQUAL(i.t, comps.m_t, 0);
  CHECK(Point(0,0,-1) == comps.m_point);
  CHECK(Vector(0,0,-1) == comps.m_eyev);
  CHECK(Vector(0,0,-1) == comps.m_normalv);

  r.origin = Point(0,0,0);
  Intersection i2(1, shape);
  comps = prepare_computations(i2, r);
  DOUBLES_EQUAL(i2.t, comps.m_t, 1);
  CHECK(Point(0,0,1) == comps.m_point);
  CHECK(Vector(0,0,-1) == comps.m_eyev);
  CHECK(Vector(0,0,-1) == comps.m_normalv);

  r = Ray(Point(0,0,-5),Vector(0,0,1));
  shape = std::make_shared<Sphere>();
  shape->m_transform = translation(0,0,1);
  i = Intersection(5, shape);
  comps = prepare_computations(i, r);
  CHECK(comps.m_over_point.z < -EPSILON/2);
  CHECK(comps.m_point.z > comps.m_over_point.z);
}