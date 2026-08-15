cmake_minimum_required(VERSION 3.10)

project(Slownik)
set(CMAKE_CXX_STANDARD 20)

add_executable(slownik main.cpp
        HashMap.cpp
        HashMap.h
)
