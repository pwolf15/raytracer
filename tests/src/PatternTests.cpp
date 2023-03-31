#include "CppUTest/CommandLineTestRunner.h"

#include "Color.h"
#include "Pattern.h"
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
}