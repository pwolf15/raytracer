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

TEST(Pattern, StripeAtObject)
{
    Color white(1.0,1.0,1.0);
    Color black(0.0,0.0,0.0);

    // Stripes with an object transformation
    std::shared_ptr<Sphere> object = std::make_shared<Sphere>();
    object->set_transform(scaling(2,2,2));
    Pattern pattern = stripe_pattern(white, black);
    Color c = stripe_at_object(pattern, object, Point(1.5, 0, 0));
    CHECK(white == c);

    // Stripes with a pattern transformation
    std::shared_ptr<Sphere> object2 = std::make_shared<Sphere>();
    pattern.m_transform = scaling(2,2,2);
    c = stripe_at_object(pattern, object2, Point(1.5,0,0));
    CHECK(white == c);

    // Stripes with both an object and a pattern transformation
    std::shared_ptr<Sphere> object3 = std::make_shared<Sphere>();
    object->set_transform(scaling(2,2,2));
    pattern = stripe_pattern(white, black);
    pattern.m_transform = translation(0.5,0,0);
    c = stripe_at_object(pattern, object3, Point(2.5, 0, 0));
    CHECK(white == c);
}