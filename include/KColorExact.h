//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#ifndef KCOLOREXACT_H
#define KCOLOREXACT_H

#include "Graph.h"
#include <vector>

// IMPORTANTE: Incluimos esto para que KColorExact reconozca el struct "ColoringResult"
// que definimos anteriormente en DSATUR.h (o Graph.h).
#include "DSATUR.h"

class KColorExact {
public:
    // Solves the graph coloring using Exact Backtracking.
    ColoringResult solve(const Graph& g);
};

#endif //KCOLOREXACT_H