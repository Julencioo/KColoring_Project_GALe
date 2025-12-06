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

// Limit to prevent Exact algorithm from freezing execution on huge graphs
const int LIMIT_EXACT = 70;

int main(int argc, char* argv[]) {
    Graph g;
    std::string filename;

    // 1. Argument Parsing
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "test_graph";
        g.resize(4);
        g.add_edge(0, 1); g.add_edge(0, 2); g.add_edge(1, 2); g.add_edge(2, 3);
    }

    // 2. Load Graph
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

    std::cout << "Graph Loaded: " << filename << " (V=" << g.num_vertices() << ")\n";

    // --- ALGORITHM 1: DSATUR ---
    {
        auto start = std::chrono::high_resolution_clock::now();
        DSatur solver;
        ColoringResult result = solver.solve(g);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "CSV_RESULT,DSATUR," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << result.chromatic_number << "," << elapsed.count() << "\n";
    }

    // --- ALGORITHM 2: EXACT BACKTRACKING ---
    // Only run if graph is small enough, otherwise it hangs forever
    if (g.num_vertices() <= LIMIT_EXACT) {
        auto start = std::chrono::high_resolution_clock::now();
        KColorExact solver;
        ColoringResult result = solver.solve(g);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "CSV_RESULT,EXACT," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << result.chromatic_number << "," << elapsed.count() << "\n";
    } else {
        std::cout << "CSV_RESULT,EXACT," << filename << ","
                  << g.num_vertices() << "," << g.num_edges() << ","
                  << "SKIPPED_TOO_LARGE" << ",0.0\n";
    }

    return 0;
}