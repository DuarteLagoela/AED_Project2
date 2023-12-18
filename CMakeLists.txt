cmake_minimum_required(VERSION 3.27)
project(AED_Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_Project2 main.cpp
        source/DataSetLoader.cpp
        source/DataSetLoader.h
        source/FlightManagement.h
        source/FlightManagement.cpp
        source/Graph.h)
