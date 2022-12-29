cmake_minimum_required(VERSION 3.0)

project(raytracer)

set (CMAKE_CXX_STANDARD 20)
include_directories(include)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(main main.cpp)
add_executable(tests tests.cpp)
add_executable(cannon cannon.cpp)
target_link_libraries(main spdlog fmt)
target_link_libraries(tests CppUTest spdlog fmt)
