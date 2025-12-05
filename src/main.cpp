//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "Graph.h"
#include "DSATUR.h"

int main(int argc, char* argv[]) {
    Graph g;
    std::string filename;

    // 1. Argument Parsing
    if (argc > 1) {
        filename = argv[1];
    } else {
        // Default internal test
        std::cout << "Usage: " << argv[0] << " <graph_file>\n";
        std::cout << "No file provided. Running Triangle Test...\n";
        g.resize(4);
        g.add_edge(0, 1); g.add_edge(0, 2); g.add_edge(1, 2); g.add_edge(2, 3);
    }

    // 2. Load Graph
    if (!filename.empty()) {
        std::cout << "Loading graph from " << filename << "...\n";
        bool success = false;

        // Check extension to decide which loader to use
        if (filename.find(".txt") != std::string::npos) {
            std::cout << "[Info] Detected .txt extension. Using simple edge loader (load_from_file2).\n";
            success = g.load_from_file2(filename);
        } else {
            std::cout << "[Info] Assuming DIMACS format (.col). Using standard loader.\n";
            success = g.load_from_file(filename);
        }

        if (!success) {
            std::cerr << "CRITICAL ERROR: Failed to load graph.\n";
            return 1;
        }
    }

    std::cout << "Graph Specs: V=" << g.num_vertices() << ", E=" << g.num_edges() << "\n";

    // 3. Run DSATUR
    std::cout << "\n[Running DSATUR]...\n";
    auto start = std::chrono::high_resolution_clock::now();

    DSatur solver;
    ColoringResult result = solver.solve(g);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // 4. Output Results
    std::cout << "--- Results ---\n";
    std::cout << "Algorithm: DSATUR\n";
    std::cout << "Chromatic Number (k): " << result.chromatic_number << "\n";
    std::cout << "Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " seconds\n";

    // CSV Output
    std::cout << "CSV_RESULT,DSATUR," << (filename.empty() ? "TEST" : filename) << ","
              << g.num_vertices() << "," << g.num_edges() << ","
              << result.chromatic_number << "," << elapsed.count() << "\n";

    return 0;
}