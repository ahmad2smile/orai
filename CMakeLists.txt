cmake_minimum_required(VERSION 3.25)
project(orai)

set(CMAKE_CXX_STANDARD 23)

add_executable(orai src/main.cpp
        src/Statement.cpp
        src/Statement.h
        src/Shell.cpp
        src/Shell.h)
