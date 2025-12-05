//
// Created by Eduardo Martín Postigo (xmartie01) on 04/12/2025.
//

#ifndef DSATUR_H
#define DSATUR_H

#include "Graph.h"
#include <vector>

// Struct to hold the results.
// Defined here to avoid modifying Graph.h
struct ColoringResult {
    int chromatic_number;        // The 'k' (number of colors used)
    std::vector<int> assignment; // assignment[v] = color_id
};

class DSatur {
public:
    // Solves the graph coloring using the DSATUR heuristic
    ColoringResult solve(const Graph& g);
};

#endif //DSATUR_H