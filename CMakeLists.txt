cmake_minimum_required(VERSION 3.10)
project(KColoring_Project_GALe)

set(CMAKE_CXX_STANDARD 14)

# 1. Include the header directory so we can use #include "Graph.h" easily
include_directories(include)

# 2. Define the executable and LIST ALL .cpp FILES here
add_executable(kcoloring
        src/main.cpp
        src/Graph.cpp
        src/DSATUR.cpp
)