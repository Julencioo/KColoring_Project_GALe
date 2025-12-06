cmake_minimum_required(VERSION 3.26)
project(KColoring_Project_GALe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir las fuentes del proyecto
# Asegúrate de incluir todos los .cpp de los algoritmos que usas en main.cpp
add_executable(KColoring
        src/main.cpp
        src/Graph.cpp
        src/DSATUR.cpp        # Algoritmo 1
        src/KColorExact.cpp   # Algoritmo 2 (Exacto)

        # Archivos de cabecera (opcional incluirlos aquí, ayuda a que aparezcan en algunos IDEs)
        include/Graph.h
        include/DSATUR.h
        include/KColorExact.h
)

# Indicar dónde buscar los archivos .h (#include "...")
target_include_directories(KColoring PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)