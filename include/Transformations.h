#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "Matrix.h"

Matrix translation(float x, float y, float z)
{
    Matrix m({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    });
    return m;
}

Matrix scaling(float x, float y, float z)
{
    Matrix m({
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    });
    return m;
}

Matrix rotation_x(float rad)
{
    Matrix m({
        {1,0,0,0},
        {0,cos(rad),-sin(rad),0},
        {0,sin(rad),cos(rad),0},
        {0,0,0,1}
    });
    return m;
}

Matrix rotation_y(float rad)
{
    Matrix m({
        {cos(rad),0,sin(rad),0},
        {0,1,0,0},
        {-sin(rad),0,cos(rad),0},
        {0,0,0,1}
    });
    return m;
}

Matrix rotation_z(float rad)
{
    Matrix m({
        {cos(rad),-sin(rad),0,0},
        {sin(rad),cos(rad),0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
    return m;
}


#endif