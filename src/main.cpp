//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "Graph.h"
#include "DSatur.h"
#include "KColorExact.h"

// Helper para medir tiempos de ejecución cortos promediando iteraciones
template<typename Func>
long long measure_avg_nanoseconds(Func func, int num_vertices) {
    // Si el grafo es pequeño, repetimos muchas veces para capturar el tiempo
    // Si es grande, menos repeticiones.
    int iterations = 1;
    if (num_vertices < 50) iterations = 5000;
    else if (num_vertices < 200) iterations = 1000;
    else if (num_vertices < 500) iterations = 100;
    else iterations = 1;

    auto start = std::chrono::steady_clock::now();

    for(int i = 0; i < iterations; ++i) {
        func(); // Ejecutar algoritmo
    }

    auto end = std::chrono::steady_clock::now();

    // Calcular total y dividir por iteraciones para obtener el promedio por ejecución
    auto total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return total_ns / iterations;
}

int main(int argc, char* argv[]) {
    Graph g;
    std::string filename;

    // 1. Parseo de argumentos
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "test_graph";
        g.resize(4);
        g.add_edge(0, 1); g.add_edge(0, 2); g.add_edge(1, 2); g.add_edge(2, 3);
    }

    // 2. Cargar Grafo
    if (argc > 1) {
        bool success = false;
        if (filename.find(".txt") != std::string::npos) {
            success = g.load_from_file2(filename);
        } else {
            success = g.load_from_file(filename);
        }

        if (!success) {
            std::cerr << "Error loading file.\n";
            return 1;
        }
    }

    // ---------------------------------------------------------
    // ALGORITMO 1: DSATUR
    // ---------------------------------------------------------
    {
        DSatur solver;
        ColoringResult result;

        // Ejecutamos una vez primero para obtener el resultado k (sin medir)
        result = solver.solve(g);

        // Medimos el tiempo promedio
        long long elapsed_ns = measure_avg_nanoseconds([&]() {
            DSatur s; // Creamos nueva instancia para no usar caché/estados previos
            s.solve(g);
        }, g.num_vertices());

        std::cout << "CSV_RESULT,DSATUR," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << result.chromatic_number << "," << elapsed_ns << "\n" << std::flush;
    }

    // ---------------------------------------------------------
    // ALGORITMO 2: EXACT BACKTRACKING
    // ---------------------------------------------------------
    {
        // Para el exacto, NO hacemos 1000 iteraciones si es grande porque tardaría siglos.
        // Solo aplicamos repetición si el grafo es muy pequeño (V < 20).

        KColorExact solver;
        ColoringResult result;

        // Ejecución única para validación y resultados (puede ser lenta)
        // Usamos un cronómetro simple aquí porque no queremos repetir la ejecución lenta
        auto start = std::chrono::steady_clock::now();
        result = solver.solve(g);
        auto end = std::chrono::steady_clock::now();

        long long elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Si dio 0 (caso muy raro en exacto salvo grafos triviales), forzamos medición con repetición
        if (elapsed_ns == 0 && g.num_vertices() < 20) {
             elapsed_ns = measure_avg_nanoseconds([&]() {
                KColorExact s;
                s.solve(g);
            }, g.num_vertices());
        }

        std::cout << "CSV_RESULT,EXACT," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << result.chromatic_number << "," << elapsed_ns << "\n" << std::flush;
    }

    return 0;
}