cmake_minimum_required(VERSION 3.10)
project(KColoring_Project_GALe)

set(CMAKE_CXX_STANDARD 14)

# Incluir la carpeta de cabeceras (.h)
include_directories(include)

# Definir el ejecutable y TODAS las fuentes (.cpp)
add_executable(kcoloring
        src/main.cpp
        src/Graph.cpp
        src/DSATUR.cpp
        src/KColorExact.cpp  # <--- ¡ESTA LÍNEA ES LA CLAVE!
)