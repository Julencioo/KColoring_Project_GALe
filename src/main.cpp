//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include <iostream>
#include "Graph.h"
#include "DSatur.h"

int main() {
    std::cout << "--- GALe Project: Graph Coloring (DSATUR) ---\n";

    // Example Graph (Triangle with an extra edge)
    // 0 -- 1
    // |  /
    // | /
    // 2 -- 3

    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2); // 0-1-2 form a triangle -> requires 3 colors
    g.add_edge(2, 3);

    std::cout << "Graph initialized: " << g.num_vertices() << " vertices, "
              << g.num_edges() << " edges.\n";

    DSatur solver;
    ColoringResult res = solver.solve(g);

    std::cout << "Chromatic Number found: " << res.chromatic_number << "\n";
    std::cout << "Vertex Colors:\n";
    for(int i=0; i<4; ++i) {
        std::cout << "Vertex " << i << ": Color " << res.assignment[i] << "\n";
    }

    return 0;
}