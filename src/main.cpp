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

// --- BENCHMARKING INTELIGENTE ---
// Ejecuta la función hasta que se acumule suficiente tiempo para tener una medida precisa.
template<typename Func>
long long smart_benchmark_ns(Func func) {
    // 1. Intento inicial (Single shot)
    auto t1 = std::chrono::steady_clock::now();
    func();
    auto t2 = std::chrono::steady_clock::now();

    auto single_run_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

    // Si la ejecución tardó más de 1ms (1,000,000 ns), confiamos en la medida.
    // Esto evita repetir algoritmos lentos (como Exact en grafos grandes).
    if (single_run_ns > 1000000) {
        return single_run_ns;
    }

    // 2. Si fue demasiado rápido (o 0), entramos en modo repetición.
    // Repetimos hasta que pasen al menos 50ms para promediar.
    long long count = 0;
    auto start = std::chrono::steady_clock::now();
    auto end = start;

    // Límite de tiempo: 50ms (suficiente para tener precisión de ns)
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < 50) {
        func();
        count++;
        end = std::chrono::steady_clock::now();
    }

    auto total_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // Evitar división por cero (improbable)
    return (count > 0) ? (total_ns / count) : 0;
}

int main(int argc, char* argv[]) {
    Graph g;
    std::string filename;

    // 1. Load Graph
    if (argc > 1) {
        filename = argv[1];
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
    } else {
        filename = "test_graph";
        g.resize(4);
        g.add_edge(0, 1); g.add_edge(0, 2); g.add_edge(1, 2); g.add_edge(2, 3);
    }

    // ---------------------------------------------------------
    // ALGORITMO 1: DSATUR
    // ---------------------------------------------------------
    {
        DSatur solver;
        ColoringResult result;

        // 1. Obtener resultado k (primera ejecución)
        result = solver.solve(g);

        // 2. Medir tiempo con precisión (usando nueva instancia para no afectar estado)
        long long elapsed_ns = smart_benchmark_ns([&]() {
            DSatur s;
            s.solve(g);
        });

        std::cout << "CSV_RESULT,DSATUR," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << result.chromatic_number << "," << elapsed_ns << "\n" << std::flush;
    }

    // ---------------------------------------------------------
    // ALGORITMO 2: EXACT BACKTRACKING
    // ---------------------------------------------------------
    {
        KColorExact solver;
        ColoringResult result;

        // 1. Obtener resultado k (primera ejecución)
        // Nota: En grafos grandes esto tardará, el script de Python controlará el timeout.
        result = solver.solve(g);

        // 2. Medir tiempo con el mismo sistema inteligente.
        // Si el paso 1 tardó mucho, smart_benchmark detectará >1ms y NO repetirá el bucle.
        // Si fue instantáneo (grafos pequeños), repetirá hasta tener precisión.
        long long elapsed_ns = smart_benchmark_ns([&]() {
            KColorExact s;
            s.solve(g);
        });

        std::cout << "CSV_RESULT,EXACT," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << result.chromatic_number << "," << elapsed_ns << "\n" << std::flush;
    }

    return 0;
}