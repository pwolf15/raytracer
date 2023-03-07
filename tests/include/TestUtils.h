#ifndef TEST_UTILS_H
#define TEST_UTILS_H


#include "Tuple.h"

#include "CppUTest/CommandLineTestRunner.h"

#define PI 3.14159265358979

static inline void TUPLES_EQUAL(const Tuple& a, const Tuple& b, double th = 0.1)
{
  DOUBLES_EQUAL(a.x, b.x, th);
  DOUBLES_EQUAL(a.y, b.y, th);
  DOUBLES_EQUAL(a.z, b.z, th);
  DOUBLES_EQUAL(a.w, b.w, th);
}

#endif