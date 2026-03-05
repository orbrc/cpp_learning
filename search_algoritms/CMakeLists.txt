cmake_minimum_required(VERSION 4.1)
project(baseAlgoritms)

set(CMAKE_CXX_STANDARD 20)

add_executable(baseAlgoritms main.cpp
        algo/ArraySearch.cpp
        algo/ArraySearch.h)
