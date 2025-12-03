cmake_minimum_required(VERSION 3.26)
project(KColoring_Project_GALe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(KColoring
        src/main.cpp
        src/Graph.cpp
        src/KColorExact.cpp
)

# Para que pueda encontrar "Graph.h" y "KColorExact.h"
target_include_directories(KColoring PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)