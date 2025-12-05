//
// Created by Eduardo Martín Postigo (xmartie01) on 04/12/2025.
//

#ifndef DSATUR_H
#define DSATUR_H

#include "Graph.h"
#include <vector>

// Struct to hold the results for experimentation/documentation
struct ColoringResult {
    int chromatic_number;        // The 'k' in k-coloring (quality of solution)
    std::vector<int> assignment; // assignment[v] = color
};

class DSatur {
public:
    // Solves the graph coloring using the DSATUR heuristic
    // Returns the number of colors used and the specific assignment
    ColoringResult solve(const Graph& g);
};

#endif //DSATUR_H