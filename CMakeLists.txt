cmake_minimum_required(VERSION 3.0)

project(raytracer)

set (CMAKE_CXX_STANDARD 20)
include_directories(include)
include_directories(/opt/homebrew/include)
include_directories(${PROJECT_SOURCE_DIR}/tests/include)
link_directories(/opt/homebrew/lib)

add_executable(main src/main.cpp)
add_executable(tests 
    tests/src/tests.cpp 
    tests/src/CameraTests.cpp
    tests/src/IntersectionTests.cpp
    tests/src/MaterialsTests.cpp
    tests/src/PatternTests.cpp
    tests/src/PlaneTests.cpp
    tests/src/ShapeTests.cpp
    tests/src/SphereTests.cpp
    tests/src/WorldTests.cpp)
add_executable(cannon src/cannon.cpp)
add_executable(clock src/clock.cpp)
add_executable(sphere2d src/sphere2d.cpp)
add_executable(simpleScene src/SimpleScene.cpp)
add_executable(simplePlane src/SimplePlane.cpp)
target_link_libraries(main spdlog fmt)
target_link_libraries(tests CppUTest spdlog fmt)
target_link_libraries(clock spdlog fmt)
target_link_libraries(sphere2d spdlog fmt)
target_link_libraries(simplePlane spdlog fmt)
