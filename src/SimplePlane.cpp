#include "Camera.h"
#include "Canvas.h"
#include "PointLight.h"
#include "Plane.h"
#include "Sphere.h"
#include "Transformations.h"
#include "Utils.h"
#include "World.h"

#define PI 3.141592653

int main()
{
    Plane floor;

    Sphere middle;
    middle.m_transform = translation(-0.5, 1, 0.5);
    middle.m_material = Material();
    middle.m_material.color = Color(0.1, 1, 0.5);
    middle.m_material.diffuse = 0.7;
    middle.m_material.specular = 0.3;

    Sphere right;
    right.m_transform = translation(1.5,0.5,-0.5) * scaling(0.5,0.5,0.5);
    right.m_material = Material();
    right.m_material.color = Color(0.5, 1, 0.1);
    right.m_material.diffuse = 0.7;
    right.m_material.specular = 0.3;

    Sphere left;
    left.m_transform = translation(-1.5,0.33,-0.75) * scaling(0.33,0.33,0.33);
    left.m_material = Material();
    left.m_material.color = Color(1,0.8,1);
    left.m_material.diffuse = 0.7;
    left.m_material.specular = 0.3;

    World world;
    world.m_lights.push_back(PointLight(Point(-10,10,-10), Color(1,1,1)));
    world.m_shapes.push_back(std::make_shared<Sphere>(left));
    world.m_shapes.push_back(std::make_shared<Sphere>(middle));
    world.m_shapes.push_back(std::make_shared<Sphere>(right));  
    world.m_shapes.push_back(std::make_shared<Plane>(floor));

    Camera camera(640,480,PI/3);
    camera.m_transform = view_transform(Point(0,1.5,-5), Point(0,1,0), Vector(0,1,0));

    Canvas canvas = render(camera, world);
    std::ofstream f("simplePlane.ppm");
    std::string ppm = canvas.canvas_to_ppm();
    f << ppm;
    f.close();

    return 0;
}