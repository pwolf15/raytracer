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

#include <fstream>
#include <iostream>


#define PI 3.14159265358979

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

TEST(Matrix, Inverse)
{
  Matrix a({
    {-5,2,6,-8},
    {1,-5,1,8},
    {7,7,-6,-7},
    {1,-3,7,4}
  });
  Matrix a_I = a.inverse();
  Matrix a_I_exp({
    {0.21805,0.45113,0.24060,-0.04511},
    {-0.80827,-1.45677,-0.44361,0.52068},
    {-0.07895,-0.22368,-0.05263,0.19737},
    {-0.52256,-0.81391,-0.30075,0.30639}
  });
  CHECK(a_I == a_I_exp);

  Matrix b({
    {8,-5,9,2},
    {7,5,6,1},
    {-6,0,9,6},
    {-3,0,-9,-4}
  });

  Matrix b_I = b.inverse();
  Matrix b_I_exp({
    {-0.15385,-0.15385,-0.28205,-0.53846},
    {-0.07692,0.12308,0.02564,0.03077},
    {0.35897,0.35897,0.43590,0.92308},
    {-0.69231,-0.69231,-0.76923,-1.92308}
  });
  CHECK(b_I == b_I_exp);

  Matrix c({
    {9,3,0,9},
    {-5,-2,-6,-3},
    {-4,9,6,4},
    {-7,6,6,2}
  });
  Matrix c_I = c.inverse();
  Matrix c_I_exp({
    {-0.04074,-0.07778,0.14444,-0.22222},
    {-0.07778,0.03333,0.36667,-0.33333},
    {-0.02901,-0.14630,-0.10926,0.12963},
    {0.17778,0.06667,-0.26667,0.33333}
  });
  CHECK(c_I == c_I_exp);

  Matrix d({
    {3,-9,7,3},
    {3,-8,2,-9},
    {-4,4,4,1},
    {-6,5,-1,1}
  });
  Matrix e({
    {8,2,2,2},
    {3,-1,7,0},
    {7,0,5,4},
    {6,-2,0,5}
  });
  Matrix f = d * e;
  Matrix g = f * e.inverse();
  CHECK(d == g);
}

TEST(Matrix, Chapter3Questions)
{
  // inverse of identity == identity
  Matrix a({
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
  });
  Matrix a_I = a.inverse();
  CHECK(a_I == a);

  // product of matrix with its inverse == identity
  Matrix b({
    {8,2,2,2},
    {3,-1,7,0},
    {7,0,5,4},
    {6,-2,0,5}
  });

  Matrix b_I = b.inverse();
  Matrix c = b * b_I;
  CHECK(c == a);

  // tranpose of inverse == inverse of tranpose
  Matrix bT = b.transpose();
  Matrix bT_I = bT.inverse();
  Matrix bI = b.inverse();
  Matrix bI_T = bI.transpose();
  CHECK(bT_I == bI_T);

  // changing one element of identity matrix
  // results in multiplying associated element by scalar factor
  Matrix d({
    {5,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
  });
  Tuple t({0.1,0.2,0.3,0.4});
  Tuple r = d*t;
  std::cout << r.x << "," << r.y << "," << r.z << "," << r.w << std::endl;


}

TEST_GROUP(Transformations)
{

};

TEST(Transformations, Translate)
{
  // point translation works
  Matrix t = translation(5, -3, 2);
  Point p({-3, 4, 5});
  Point tp = t * p;
  Point tp_exp({2,1,7});

  CHECK(tp == tp_exp);

  // inverse translation
  Matrix tI = t.inverse();
  Point pI = tI * p;
  Point pI_exp({-8,7,3});

  CHECK(pI == pI_exp);

  // vector translation
  Vector v({-3,4,5});
  Vector tv = t * v;
  Vector tv_exp({-3,4,5});

  CHECK(tv == tv_exp);
}

TEST(Transformations, Scale)
{
  Matrix s = scaling(2, 3, 4);
  Point p({-4, 6, 8});
  Point sP = s * p;
  Point sP_exp({-8, 18, 32});

  CHECK(sP_exp == sP);

  Vector v({-4,6,8});
  Vector sV = s * v;
  Vector sV_exp({-8, 18, 32});

  CHECK(sV_exp == sV);

  // inverse
  Matrix sI = s.inverse();
  Vector sIV_exp({-2, 2, 2});
  Vector sIV = sI * v;

  CHECK(sIV_exp == sIV);

  // reflection
  Matrix r = scaling(-1, 1, 1);
  Point p2({2, 3, 4});
  Point p2r = r * p2;
  Point p2R_exp({-2, 3, 4});

  CHECK(p2r == p2R_exp);
}

TEST(Transformations, RotateX)
{
  Point p({0,1,0});
  Matrix half_quarter = rotation_x(PI / 4);
  Matrix full_quarter = rotation_x(PI / 2);
  Point p1 = half_quarter * p;
  Point p2 = full_quarter * p;
  Point p1_exp({0, sqrtf(2)/2, sqrtf(2)/2});
  Point p2_exp({0, 0, 1});

  CHECK(p1 == p1_exp);
  CHECK(p2 == p2_exp);
}

TEST(Transformations, RotateY)
{
  Point p({0,0,1});
  Matrix half_quarter = rotation_y(PI / 4);
  Matrix full_quarter = rotation_y(PI / 2);
  Point p1 = half_quarter * p;
  Point p2 = full_quarter * p;
  Point p1_exp({sqrtf(2)/2, 0, sqrtf(2)/2});
  Point p2_exp({1, 0, 0});

  CHECK(p1 == p1_exp);
  CHECK(p2 == p2_exp);
}

TEST(Transformations, RotateZ)
{
  Point p({0,1,0});
  Matrix half_quarter = rotation_z(PI / 4);
  Matrix full_quarter = rotation_z(PI / 2);
  Point p1 = half_quarter * p;
  Point p2 = full_quarter * p;
  Point p1_exp({-sqrtf(2)/2, sqrtf(2)/2, 0});
  Point p2_exp({-1, 0, 0});

  CHECK(p1 == p1_exp);
  CHECK(p2 == p2_exp);
}

TEST(Transformations, Shear)
{
  Point p({2,3,4});

  Matrix transform1 = shearing(1, 0, 0, 0, 0, 0);
  Point p1 = transform1 * p;
  Point p1_exp({5,3,4});
  CHECK(p1 == p1_exp);

  Matrix transform2 = shearing(0, 1, 0, 0, 0, 0);
  Point p2 = transform2 * p;
  Point p2_exp({6,3,4});
  CHECK(p2 == p2_exp);

  Matrix transform3 = shearing(0, 0, 1, 0, 0, 0);
  Point p3 = transform3 * p;
  Point p3_exp({2, 5, 4});
  CHECK(p3 == p3_exp);

  Matrix transform4 = shearing(0, 0, 0, 1, 0, 0);
  Point p4 = transform4 * p;
  Point p4_exp({2,7,4});
  CHECK(p4 == p4_exp);

  Matrix transform5 = shearing(0, 0, 0, 0, 1, 0);
  Point p5 = transform5 * p;
  Point p5_exp({2,3,6});
  CHECK(p5 == p5_exp);

  Matrix transform6 = shearing(0, 0, 0, 0, 0, 1);
  Point p6 = transform6 * p;
  Point p6_exp({2,3,7});
  CHECK(p6 == p6_exp);
}

TEST(Transformations, Chaining)
{
  // individual transformations
  Point p({1,0,1});
  Matrix A = rotation_x(PI / 2);
  Matrix B = scaling(5,5,5);
  Matrix C = translation(10,5,7);

  // rotation
  Point p2 = A * p;
  Point p2_exp({1, -1, 0});
  CHECK(p2_exp == p2);

  // scaling
  Point p3 = B * p2;
  Point p3_exp({5, -5, 0});
  CHECK(p3_exp == p3);

  // translation
  Point p4 = C * p3;
  Point p4_exp({15, 0, 7});
  CHECK(p4_exp == p4);

  // chained
  Matrix T = C * B * A;
  Point p5 = T * p;
  CHECK(p4_exp == p5);
}

TEST_GROUP(Rays)
{

};

TEST(Rays, Rays)
{
  Point origin({1,2,3});
  Vector direction({4,5,6});
  Ray ray(origin, direction);

  CHECK(ray.origin == origin);
  CHECK(ray.direction == direction);
}

TEST(Rays, Position)
{
  Ray ray(Point({2,3,4}), Vector({1,0,0}));
  CHECK(ray.position(0) == Point({2,3,4}));
  CHECK(ray.position(1) == Point({3,3,4}));
  CHECK(ray.position(-1) == Point({1,3,4}));
  CHECK(ray.position(2.5) == Point({4.5,3,4}));
}

TEST(Rays, Intersect)
{
  Ray ray(Point({0,0,-5}), Vector({0,0,1}));
  Sphere s;
  std::vector<float> xs = s.intersect(ray);
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(4.0, xs[0], 0);
  DOUBLES_EQUAL(6.0, xs[1], 0);

  Ray ray2(Point({0,1,-5}), Vector({0,0,1}));
  xs = s.intersect(ray2);
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(5.0, xs[0], 0);
  DOUBLES_EQUAL(5.0, xs[1], 0);

  Ray ray3(Point({0,2,-5}), Vector({0,0,1}));
  xs = s.intersect(ray3);
  CHECK_EQUAL(0, xs.size());

  Ray ray4(Point({0,0,0}), Vector({0,0,1}));
  xs = s.intersect(ray4);
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(-1.0, xs[0], 0);
  DOUBLES_EQUAL(1.0, xs[1], 0);

  Ray ray5(Point({0,0,5}), Vector({0,0,1}));
  xs = s.intersect(ray5);
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(-6.0, xs[0], 0);
  DOUBLES_EQUAL(-4.0, xs[1], 0);
}

TEST_GROUP(Intersection)
{

};

TEST(Intersection, Intersection)
{
  Sphere s;
  Intersection i(3.5, &s);

  DOUBLES_EQUAL(3.5, i.t, 0);
  CHECK(&s == i.object);
}

TEST(Intersection, Intersections)
{
  Sphere s;
  Intersection i1(1, &s), i2(2, &s);
  std::vector<Intersection> xs = intersections({i1, i2});
  CHECK_EQUAL(2, xs.size());
  DOUBLES_EQUAL(1, xs[0].t, 0);
  DOUBLES_EQUAL(2, xs[1].t, 0);
}

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}
