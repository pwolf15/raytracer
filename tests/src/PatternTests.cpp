#include "CppUTest/CommandLineTestRunner.h"

#include "Color.h"
#include "Pattern.h"
#include "Point.h"
#include "Utils.h"

TEST_GROUP(Pattern)
{

};

TEST(Pattern, Pattern)
{
    Color white(1.0,1.0,1.0);
    Color black(0.0,0.0,0.0);

    // Creating a striped pattern
    Pattern p = stripe_pattern(white, black);
    CHECK(white == p.m_a);
    CHECK(black == p.m_b);

    // A stripe pattern is constant in y
    CHECK(white == stripe_at(p, Point(0,0,0)));
    CHECK(white == stripe_at(p, Point(0,1,0)));
    CHECK(white == stripe_at(p, Point(0,2,0)));

    // A stripe pattern is constant in z
    CHECK(white == stripe_at(p, Point(0,0,0)));
    CHECK(white == stripe_at(p, Point(0,0,1)));
    CHECK(white == stripe_at(p, Point(0,0,2)));

    // A stripe pattern alternates in x
    CHECK(white == stripe_at(p, Point(0,0,0)));
    CHECK(white == stripe_at(p, Point(0.9,0,0)));
    CHECK(black == stripe_at(p, Point(1,0,0)));
    CHECK(black == stripe_at(p, Point(-0.1,0,0)));
    CHECK(black == stripe_at(p, Point(-1,0,0)));
    CHECK(white == stripe_at(p, Point(-1.1,0,0)));
}