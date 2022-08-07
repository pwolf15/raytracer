#include "CppUTest/CommandLineTestRunner.h"

#include "Tuple.h"
#include "Point.h"
#include "Vector.h"

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
};

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}