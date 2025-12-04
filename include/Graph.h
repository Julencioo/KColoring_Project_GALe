//
// Created by Juelen and Eduardo (YOUR_LOGIN)
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph {
private:
    int V; // Number of vertices
    int E; // Number of edges
    std::vector<std::vector<int>> adj; // Adjacency list

public:
    // Constructor
    Graph(int V);

    // Add an undirected edge
    void add_edge(int u, int v);

    // Get number of vertices
    int num_vertices() const;

    // Get number of edges
    int num_edges() const;

    // Get degree of a vertex
    int degree(int v) const;

    // Get neighbors of a vertex
    const std::vector<int>& neighbors(int v) const;

    // Debug: Print graph structure
    void print() const;
};

#endif //GRAPH_H