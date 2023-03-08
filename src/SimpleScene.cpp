#include "Camera.h"
#include "Canvas.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Transformations.h"
#include "Utils.h"
#include "World.h"

#define PI 3.141592653

int main()
{
    Sphere floor;
    floor.transform = scaling(10, 0.01, 10);
    floor.material = Material();
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere left_wall;
    left_wall.transform = translation(0, 0, 5) * rotation_y(-PI/4) * rotation_x(PI/2) * scaling(10, 0.01, 10);
    left_wall.material = floor.material;

    Sphere right_wall;
    right_wall.transform = translation(0,0,5) * rotation_y(PI/4) * rotation_x(PI/2) * scaling(10,0.01,10);
    right_wall.material = floor.material;

    Sphere middle;
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material = Material();
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right;
    right.transform = translation(1.5,0.5,-0.5) * scaling(0.5,0.5,0.5);
    right.material = Material();
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left;
    left.transform = translation(-1.5,0.33,-0.75) * scaling(0.33,0.33,0.33);
    left.material = Material();
    left.material.color = Color(1,0.8,1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    World world;
    world.m_lights.push_back(PointLight(Point(-10,10,-10), Color(1,1,1)));
    world.m_spheres.push_back(std::make_shared<Sphere>(left));
    world.m_spheres.push_back(std::make_shared<Sphere>(middle));
    world.m_spheres.push_back(std::make_shared<Sphere>(right));  
    world.m_spheres.push_back(std::make_shared<Sphere>(floor));
    world.m_spheres.push_back(std::make_shared<Sphere>(left_wall));
    world.m_spheres.push_back(std::make_shared<Sphere>(right_wall));

    Camera camera(640,480,PI/3);
    camera.m_transform = view_transform(Point(0,1.5,-5), Point(0,1,0), Vector(0,1,0));
    
    Canvas canvas = render(camera, world);
    std::ofstream f("simpleScene.ppm");
    std::string ppm = canvas.canvas_to_ppm();
    f << ppm;
    f.close();

    return 0;
}