cmake_minimum_required(VERSION 3.8)

project(newyeartracing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -O1 -g -fsanitize=address -fno-omit-frame-pointer")

add_executable(
    tracer
    main.cpp
    material.hpp
    camera.hpp
    interval.hpp
    sphere.hpp
    hittable.hpp
    rtweekend.hpp
    ray.hpp
    color.hpp
    vec3.hpp
)
