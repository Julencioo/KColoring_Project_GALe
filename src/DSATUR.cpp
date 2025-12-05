//
// Created by Eduardo Martín Postigo (xmartie01) on 04/12/2025.
//

#include "DSATUR.h"
#include <vector>
#include <set>
#include <algorithm>

ColoringResult DSatur::solve(const Graph& g) {
    int n = g.num_vertices();

    // Vector to store the assigned color for each vertex. -1 means uncolored.
    std::vector<int> assignment(n, -1);

    // Saturation: A set of unique colors used by neighbors for each vertex.
    std::vector<std::set<int>> neighbor_colors(n);

    // Pre-calculate degrees for the tie-breaking rule (Step 2b)
    std::vector<int> degrees(n);
    for(int i = 0; i < n; ++i) {
        degrees[i] = g.degree(i);
    }

    int vertices_colored = 0;

    while (vertices_colored < n) {
        int best_vertex = -1;
        int max_sat = -1;
        int max_deg = -1;

        // --- SELECTION HEURISTIC ---
        for (int v = 0; v < n; ++v) {
            if (assignment[v] == -1) { // Process only uncolored vertices

                int current_sat = (int)neighbor_colors[v].size();
                int current_deg = degrees[v];

                bool is_better = false;

                if (best_vertex == -1) {
                    is_better = true;
                } else {
                    // 1. Primary Criteria: Max Saturation
                    if (current_sat > max_sat) {
                        is_better = true;
                    }
                    // 2. Secondary Criteria (Tie-Breaker): Max Degree
                    else if (current_sat == max_sat) {
                        if (current_deg > max_deg) {
                            is_better = true;
                        }
                    }
                }

                if (is_better) {
                    best_vertex = v;
                    max_sat = current_sat;
                    max_deg = current_deg;
                }
            }
        }

        if (best_vertex == -1) break; // Should not happen if vertices_colored < n

        // --- COLOR ASSIGNMENT ---
        // Find the smallest color (0, 1, 2...) NOT in neighbor_colors[best_vertex]
        int color = 0;
        while (neighbor_colors[best_vertex].count(color)) {
            color++;
        }

        assignment[best_vertex] = color;
        vertices_colored++;

        // --- UPDATE NEIGHBORS ---
        for (int neighbor : g.neighbors(best_vertex)) {
            if (assignment[neighbor] == -1) {
                neighbor_colors[neighbor].insert(color);
            }
        }
    }

    // Calculate chromatic number
    int max_color_used = 0;
    for (int c : assignment) {
        if (c > max_color_used) max_color_used = c;
    }

    // Handle edge case of empty graph
    int k = (n == 0) ? 0 : (max_color_used + 1);

    return {k, assignment};
}