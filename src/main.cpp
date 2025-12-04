//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include <iostream>
#include <chrono> // For measuring time
#include "Graph.h"
#include "DSatur.h"

int main(int argc, char* argv[]) {
    Graph g;

    // Check if filename is provided
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <graph_file.col>\n";
        std::cout << "Running default internal test...\n";

        // Default test case (Triangle)
        g.resize(4);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        g.add_edge(1, 2);
        g.add_edge(2, 3);
    } else {
        std::string filename = argv[1];
        std::cout << "Loading graph from " << filename << "...\n";
        if (!g.load_from_file(filename)) {
            return 1;
        }
    }

    std::cout << "Graph Specs: V=" << g.num_vertices() << ", E=" << g.num_edges() << "\n";

    // Measure Time
    auto start = std::chrono::high_resolution_clock::now();

    DSatur solver;
    ColoringResult result = solver.solve(g);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output for human reading
    std::cout << "--- Results ---\n";
    std::cout << "Algorithm: DSATUR\n";
    std::cout << "Chromatic Number (k): " << result.chromatic_number << "\n";
    std::cout << "Time: " << elapsed.count() << " seconds\n";

    // Output valid for CSV parsing (Automation)
    // Format: CSV_RESULT,Vertices,Edges,Colors,Time
    std::cout << "CSV_RESULT," << g.num_vertices() << "," << g.num_edges()
              << "," << result.chromatic_number << "," << elapsed.count() << "\n";

    return 0;
}