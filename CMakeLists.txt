cmake_minimum_required(VERSION 3.0)

project(raytracer)

set (CMAKE_CXX_STANDARD 20)
include_directories(include)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(main main.cpp)
add_executable(tests tests.cpp tests/src/CameraTests.cpp)
add_executable(cannon cannon.cpp)
add_executable(clock clock.cpp)
add_executable(sphere2d sphere2d.cpp)
target_link_libraries(main spdlog fmt)
target_link_libraries(tests CppUTest spdlog fmt)
target_link_libraries(clock spdlog fmt)
target_link_libraries(sphere2d spdlog fmt)
