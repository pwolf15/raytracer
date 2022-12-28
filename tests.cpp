#include "CppUTest/CommandLineTestRunner.h"

#include "Tuple.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"

#include <fstream>
#include <iostream>

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

  // addition
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color c3 = c1 + c2;
  DOUBLES_EQUAL(c3.red(), 1.6, t);
  DOUBLES_EQUAL(c3.green(), 0.7, t);
  DOUBLES_EQUAL(c3.blue(), 1.0, t);

  // subtraction
  Color c4 = c1 - c2;
  DOUBLES_EQUAL(c4.red(), 0.2, t);
  DOUBLES_EQUAL(c4.green(), 0.5, t);
  DOUBLES_EQUAL(c4.blue(), 0.5, t);

  // scalar multiplication
  Color c5(0.2, 0.3, 0.4);
  Color c6 = c5 * 2;
  DOUBLES_EQUAL(c6.red(), 0.4, t);
  DOUBLES_EQUAL(c6.green(), 0.6, t);
  DOUBLES_EQUAL(c6.blue(), 0.8, t);

  // multiplication (Hadamard product)
  Color c7(1, 0.2, 0.4);
  Color c8(0.9, 1, 0.1);
  Color c9 = c7 * c8;
  DOUBLES_EQUAL(c9.red(), 0.9, t);
  DOUBLES_EQUAL(c9.green(), 0.2, t);
  DOUBLES_EQUAL(c9.blue(), 0.04, t);
};

TEST_GROUP(Canvas)
{

};

TEST(Canvas, Canvas1)
{
  int w = 10, h = 20;
  double t = 1e-6;

  // constructor
  Canvas c1(10, 20);
  CHECK_EQUAL(w, c1.width);
  CHECK_EQUAL(h, c1.height);

  for (size_t i = 0; i < h; ++i)
  {
    for (size_t j = 0; j < w; ++j)
    {
      DOUBLES_EQUAL(0, c1.pixels[i*w+j].red(), t);
      DOUBLES_EQUAL(0, c1.pixels[i*w+j].green(), t);
      DOUBLES_EQUAL(0, c1.pixels[i*w+j].blue(), t);
    }
  }

  // pixel write/access
  c1.write_pixel(2, 3, Color{1, 0, 0});
  Color col = c1.pixel_at(2, 3);
  DOUBLES_EQUAL(1, col.red(), t);
  DOUBLES_EQUAL(0, col.green(), t);
  DOUBLES_EQUAL(0, col.blue(), t);

  // canvas
  Canvas c2(5, 3);
  Color col1(1.5, 0, 0), col2(0, 0.5, 0), col3(-0.5, 0, 1);
  c2.write_pixel(0, 0, col1);
  c2.write_pixel(2, 1, col2);
  c2.write_pixel(4, 2, col3);
  std::string ppm = c2.canvas_to_ppm();
  std::cout << "PPM" << "\n" << ppm << std::endl;
  CHECK('\n' == ppm[ppm.length() - 1]);

  Canvas c3(512, 512);
  Color col4(1, 1, 0);
  for (int i = 0; i < 512; ++i)
  {
    for (int j = 0; j < 512; ++j)
    {
      c3.write_pixel(j, i, col4);
    }
  }

  ppm = c3.canvas_to_ppm();
  // std::cout << "PPM2" << "\n" << ppm << std::endl;

  std::ofstream f("test.ppm");
  f << ppm;
  f.close();



  CHECK('\n' == ppm[ppm.length() - 1]);
};

TEST_GROUP(Matrix)
{

};

TEST(Matrix, Matrix1)
{
  Matrix m1(std::vector<std::vector<float>>{
    {
      {1, 2, 3, 4},
      { 5.5, 6.5, 7.5, 8.5},
      { 9, 10, 11, 12},
      { 13.5, 14.5, 15.5, 16.5}
    }
  });

  double t = 0.01;
  DOUBLES_EQUAL(1, m1(0, 0), t);
  DOUBLES_EQUAL(4, m1(0, 3), t);
  DOUBLES_EQUAL(5.5, m1(1, 0), t);
  DOUBLES_EQUAL(7.5, m1(1, 2), t);
  DOUBLES_EQUAL(11, m1(2, 2), t);
  DOUBLES_EQUAL(13.5, m1(3, 0), t);
  DOUBLES_EQUAL(15.5, m1(3, 2), 15.5);

  Matrix m2({
    {-3, 5},
    {1, -2}
  });

  DOUBLES_EQUAL(-3, m2(0, 0), t);
  DOUBLES_EQUAL(5, m2(0, 1), t);
  DOUBLES_EQUAL(1, m2(1,0), t);
  DOUBLES_EQUAL(-2, m2(1,1), t);

  Matrix m3({
    { -3,5,0 },
    { 1,-2,-7 },
    { 0, 1, 1 }
  });

  DOUBLES_EQUAL(-3, m3(0,0), t);
  DOUBLES_EQUAL(-2, m3(1,1), t);
  DOUBLES_EQUAL(1, m3(2,2), t);
};

TEST(Matrix, Equality)
{
  Matrix a({
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  });
  Matrix b({
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  });
  CHECK(a == b);

  Matrix c({
    { 2, 3, 4, 5},
    { 6, 7, 8, 9},
    { 8, 7, 6, 5},
    { 4, 3, 2, 1}
  });

  CHECK (a != c);
}

TEST(Matrix, Multiply)
{
  Matrix a({
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  });

  Matrix b({
    {-2, 1, 2, 3},
    {3, 2, 1, -1},
    {4,3,6,5},
    {1,2,7,8}
  });

  Matrix c = a * b;
  Matrix exp_c({
    { 20, 22, 50, 48 },
    { 44, 54, 114, 108 },
    { 40, 58, 110, 102 },
    { 16, 26, 46, 42 }
  });

  std::cout << c(2, 2) << std::endl;

  CHECK(c == exp_c);
}

TEST(Matrix, Multiply2)
{
  Matrix a({
    {1,2,3,4},
    {2,4,4,2},
    {8,6,4,1},
    {0,0,0,1}
  });

  Tuple b(1,2,3,1);

  Tuple c = a*b;

  Tuple c_exp(18,24,33,1);
  
  std::cout << c.z << std::endl;
  CHECK(c == c_exp);
}

TEST(Matrix, Identity)
{
  Matrix a({
    {0,1,2,4},
    {1,2,4,8},
    {2,4,8,16},
    {4,8,16,32}
  });
  Matrix i({
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
  });
  Matrix b = a * i;
  CHECK(b == a);

  // transpose
  Matrix i_T = i.transpose();
  CHECK(i_T == i);
}

TEST(Matrix, Transpose)
{
  Matrix a({
    {0,9,3,0},
    {9,8,0,8},
    {1,8,5,3},
    {0,0,5,0}
  });
  Matrix a_T = a.transpose();
  Matrix a_T_exp({
    {0,9,1,0},
    {9,8,8,0},
    {3,0,5,5},
    {0,8,3,0}
  });
  CHECK(a_T == a_T_exp);
}

TEST(Matrix, Determinant)
{
  Matrix a({
    {1,5},
    {-3,2}
  });
  double t = 0.1;
  DOUBLES_EQUAL(17, a.determinant(), t);

  Matrix b({
    {1,2,6},
    {-5,8,-4},
    {2,6,4}
  });
  DOUBLES_EQUAL(-196, b.determinant(), t);

  Matrix c({
    {-2,-8,3,5},
    {-3,1,7,3},
    {1,2,-9,6},
    {-6,7,7,-9}
  });
  DOUBLES_EQUAL(-4071, c.determinant(), t);
}

TEST(Matrix, Submatrix)
{
  Matrix a({
    {1,5,0},
    {-3,2,7},
    {0,6,-3}
  });
  Matrix b = a.submatrix(0, 2);
  Matrix b_exp({
    {-3,2},
    {0,6}
  });
  CHECK(b_exp == b);

  Matrix a2({
    {-6,1,1,6},
    {-8,5,8,6},
    {-1,0,8,2},
    {-7,1,-1,1}
  });
  Matrix b2 = a2.submatrix(2,1);
  Matrix b2_exp({
    {-6,1,6},
    {-8,8,6},
    {-7,-1,1}
  });
  CHECK(b2_exp == b2);
}

TEST(Matrix, Minor)
{
  Matrix a({
    {3,5,0},
    {2,-1,-7},
    {6,-1,5}
  });
  double t = 0.1;
  DOUBLES_EQUAL(25, a.minor(1, 0), t);
}

TEST(Matrix, Cofactor)
{
  Matrix a({
    {3, 5, 0},
    {2,-1,-7},
    {6,-1,5}
  });
  double t = 0.1;
  DOUBLES_EQUAL(-12, a.cofactor(0, 0), t);
  DOUBLES_EQUAL(-25, a.cofactor(1, 0), t);
}

TEST(Matrix, Invertible)
{
  Matrix a({
    {6,4,4,4},
    {5,5,7,6},
    {4,-9,3,-7},
    {9,1,7,-6}
  });

  double t = 0.1;
  DOUBLES_EQUAL(-2120, a.determinant(), t);
  CHECK(a.invertible());

  Matrix b({
    {-4,2,-2,-3},
    {9,6,2,6},
    {0,-5,1,-5},
    {0,0,0,0}
  });
  DOUBLES_EQUAL(0, b.determinant(), t);
  CHECK(!b.invertible());
}

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}
