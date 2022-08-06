cmake_minimum_required(VERSION 3.0)

project(raytracer)

include_directories(include)

add_executable(main main.cpp)
add_executable(tests tests.cpp)
target_link_libraries(tests CppUTest)