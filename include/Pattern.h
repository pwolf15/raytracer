#ifndef PATTERN_H
#define PATTERN_H

#include "Color.h"

class Pattern
{
public:
    Pattern():
        m_a(0.0,0.0,0.0),
        m_b(0.0,0.0,0.0) {}

    Color m_a;
    Color m_b;

private:

};

#endif // PATTERN_H