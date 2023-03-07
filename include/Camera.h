#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include "Matrix.h"

class Camera
{
public:
    Camera(int hsize, int vsize, double field_of_view):
        m_hsize(hsize),
        m_vsize(vsize),
        m_field_of_view(field_of_view),
        m_transform({
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        })
    {
        getPixelSize();
    }

    int m_hsize;
    int m_vsize;
    double m_field_of_view;
    double m_half_width;
    double m_half_height;
    double m_pixel_size;
    Matrix m_transform;

private:
    void getPixelSize()
    {
        double half_view = tanf(m_field_of_view / 2);
        double aspect = (double)m_hsize/m_vsize;

        double half_height = 0.0, half_width = 0.0;
        if (aspect >= 1)
        {
            m_half_width = half_view;
            m_half_height = half_view / aspect;
        }
        else
        {
            m_half_width = half_view * aspect;
            m_half_height = half_view;
        }

        m_pixel_size = (m_half_width * 2) / m_hsize;
    }
};

#endif // CAMERA_H