#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    Camera(int hsize, int vsize, float field_of_view):
        m_hsize(hsize),
        m_vsize(vsize),
        m_field_of_view(field_of_view)
    {}

    int m_hsize;
    int m_vsize;
    float m_field_of_view;
};

#endif // CAMERA_H