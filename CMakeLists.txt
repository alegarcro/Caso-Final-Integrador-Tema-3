cmake_minimum_required(VERSION 3.29)
project(Integrador)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Integrador
    main.cpp
    tiny.cpp
    tiny.h)