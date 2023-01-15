#ifndef LIGHTING_H
#define LIGHTING_H

#include "Color.h"
#include "Material.h"
#include "PointLight.h"
#include "Point.h"
#include "Vector.h"

Color lighting(Material material, PointLight light, Point point, Vector eyev, Vector normalv)
{
    Color effective_color = material.color * light.intensity;

    Vector lightv = Vector(light.position - point).normalize();

    Color ambient = effective_color * material.ambient;
    Color diffuse(0.0, 0.0, 0.0), specular(0.0,0.0,0.0);

    float light_dot_normal = lightv.dot(normalv);
    if (light_dot_normal < 0)
    {
        diffuse = Color(0.0,0.0,0.0);
        specular = Color(0.0,0.0,0.0);
    }
    else
    {
        diffuse = effective_color * material.diffuse * light_dot_normal;
        Vector reflectv = ((Vector)-lightv).reflect(normalv);
        float reflect_dot_eye = reflectv.dot(eyev);
        if (reflect_dot_eye <= 0)
        {
            specular = Color(0.0,0.0,0.0);
        }
        else
        {
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}

#endif // LIGHTING_H