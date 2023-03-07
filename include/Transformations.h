#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "Matrix.h"
#include "Vector.h"

static inline Matrix translation(double x, double y, double z)
{
    Matrix m({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    });
    return m;
}

static inline Matrix scaling(double x, double y, double z)
{
    Matrix m({
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    });
    return m;
}

static inline Matrix rotation_x(double rad)
{
    Matrix m({
        {1,0,0,0},
        {0,cos(rad),-sin(rad),0},
        {0,sin(rad),cos(rad),0},
        {0,0,0,1}
    });
    return m;
}

static inline Matrix rotation_y(double rad)
{
    Matrix m({
        {cos(rad),0,sin(rad),0},
        {0,1,0,0},
        {-sin(rad),0,cos(rad),0},
        {0,0,0,1}
    });
    return m;
}

static inline Matrix rotation_z(double rad)
{
    Matrix m({
        {cos(rad),-sin(rad),0,0},
        {sin(rad),cos(rad),0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
    return m;
}

static inline Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
    Matrix m({
        {1, xy, xz,0},
        {yx, 1, yz, 0},
        {zx, zy, 1,0},
        {0,0,0,1}
    });
    return m;
}

static inline Matrix view_transform(Point from, Point to, Vector up)
{
    Vector forward(to.x - from.x, to.y - from.y, to.z - from.z);
    forward = forward.normalize();
    Vector upn = up.normalize();
    Vector left = forward.cross(upn);
    Vector true_up = left.cross(forward);

    Matrix orientation({
        {left.x, left.y, left.z, 0},
        {true_up.x, true_up.y, true_up.z, 0},
        {-forward.x, -forward.y, -forward.z, 0},
        {0, 0, 0, 1}
    });
    return orientation * translation(-from.x, -from.y, -from.z);
}

#endif