#include "CppUTest/CommandLineTestRunner.h"

#include "Tuple.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"

TEST_GROUP(Tuple)
{
};

TEST(Tuple, Tuple1)
{
  Tuple a(4.3, -4.2, 3.1, 1.0);

  // point
  double t = 1e-6;
  DOUBLES_EQUAL(4.3, a.x, t);
  DOUBLES_EQUAL(-4.2, a.y, t);
  DOUBLES_EQUAL(3.1, a.z, t);
  DOUBLES_EQUAL(1.0, a.w, t);
  CHECK(a.isPoint());

  // vector
  a.w = 0.0;
  CHECK(a.isVector());

  // equality
  Tuple b(1,2,3,4),c(1,2,3,4);
  CHECK(b == c);
  c.w = -4;
  CHECK(b != c);

  // addition
  Tuple d = b + c;
  DOUBLES_EQUAL(2, d.x, t);
  DOUBLES_EQUAL(4, d.y, t);
  DOUBLES_EQUAL(6, d.z, t);
  DOUBLES_EQUAL(0, d.w, t);

  // subtraction
  Point p1(3, 2, 1), p2(5, 6, 7);
  Point p3 = p1 - p2;
  DOUBLES_EQUAL(-2, p3.x, t);
  DOUBLES_EQUAL(-4, p3.y, t);
  DOUBLES_EQUAL(-6, p3.z, t);

  Vector v1(5,6,7);
  Point p4 = p1 - v1;
  DOUBLES_EQUAL(-2, p4.x, t);
  DOUBLES_EQUAL(-4, p4.y, t);
  DOUBLES_EQUAL(-6, p4.z, t);

  Vector v2(3, 2, 1);
  Vector v3 = v2 - v1;
  DOUBLES_EQUAL(-2, v3.x, t);
  DOUBLES_EQUAL(-4, v3.y, t);
  DOUBLES_EQUAL(-6, v3.z, t);

  // unary minus
  Tuple t1(1, -2, 3, -4);
  Tuple t2 = -t1;
  DOUBLES_EQUAL(-1, t2.x, t);
  DOUBLES_EQUAL(2, t2.y, t);
  DOUBLES_EQUAL(-3, t2.z, t);
  DOUBLES_EQUAL(4, t2.w, t);

  // multiplication
  Tuple t3 = t1 * 3.5;
  DOUBLES_EQUAL(3.5, t3.x, t);
  DOUBLES_EQUAL(-7, t3.y, t);
  DOUBLES_EQUAL(10.5, t3.z, t);
  DOUBLES_EQUAL(-14, t3.w, t); 

  Tuple t4 = t1 * 0.5;
  DOUBLES_EQUAL(0.5, t4.x, t);
  DOUBLES_EQUAL(-1, t4.y, t);
  DOUBLES_EQUAL(1.5, t4.z, t);
  DOUBLES_EQUAL(-2, t4.w, t);

  // division
  Tuple t5 = t1 / 2;
  DOUBLES_EQUAL(0.5, t5.x, t);
  DOUBLES_EQUAL(-1, t5.y, t);
  DOUBLES_EQUAL(1.5, t5.z, t);
  DOUBLES_EQUAL(-2, t5.w, t);
}

TEST_GROUP(Point)
{

};

TEST(Point, Point1)
{
  Point p(4, -4, 3);
  double t = 1e-6;
  DOUBLES_EQUAL(4, p.x, t);
  DOUBLES_EQUAL(-4, p.y, t);
  DOUBLES_EQUAL(3, p.z, t);
  DOUBLES_EQUAL(1, p.w, t);
};

TEST_GROUP(Vector)
{

};

TEST(Vector, Vector1)
{
  Vector v(4, -4, 3);
  double t = 1e-6;
  DOUBLES_EQUAL(4, v.x, t);
  DOUBLES_EQUAL(-4, v.y, t);
  DOUBLES_EQUAL(3, v.z, t);
  DOUBLES_EQUAL(0, v.w, t);

  // magnitude
  Vector v1(1, 0, 0),v2(0,1,0),v3(0,0,1),v4(1,2,3),v5(-1,-2,-3);
  DOUBLES_EQUAL(1, v1.magnitude(), t);
  DOUBLES_EQUAL(1, v2.magnitude(), t);
  DOUBLES_EQUAL(1, v3.magnitude(), t);
  DOUBLES_EQUAL(sqrt(14), v4.magnitude(), t);
  DOUBLES_EQUAL(sqrt(14), v5.magnitude(), t);

  // normalize
  Vector v6(4, 0, 0);
  Vector v7 = v6.normalize();
  DOUBLES_EQUAL(1, v7.x, t);
  DOUBLES_EQUAL(0, v7.y, t);
  DOUBLES_EQUAL(0, v7.z, t);
  DOUBLES_EQUAL(0, v7.w, t);

  Vector v8(1,2,3);
  Vector v9 = v8.normalize();
  DOUBLES_EQUAL(1/sqrt(14), v9.x, t);
  DOUBLES_EQUAL(2/sqrt(14), v9.y, t);
  DOUBLES_EQUAL(3/sqrt(14), v9.z, t);
  DOUBLES_EQUAL(0, v9.w, t);

  // dot product
  Vector v10(1,2,3),v11(2,3,4);
  DOUBLES_EQUAL(20, v10.dot(v11), t);

  // cross product
  Vector v12 = v10.cross(v11);
  DOUBLES_EQUAL(-1, v12.x, t);
  DOUBLES_EQUAL(2, v12.y, t);
  DOUBLES_EQUAL(-1, v12.z, t);

  Vector v13 = v11.cross(v10);
  DOUBLES_EQUAL(1, v13.x, t);
  DOUBLES_EQUAL(-2, v13.y, t);
  DOUBLES_EQUAL(1, v13.z, t);
};

TEST_GROUP(Color)
{

};

TEST(Color, Color1)
{
  Color c(-0.5,0.4,1.7);
  double t = 1e-6;
  DOUBLES_EQUAL(-0.5, c.red(), t);
  DOUBLES_EQUAL(0.4, c.green(), t);
  DOUBLES_EQUAL(1.7, c.blue(), t);

};

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}