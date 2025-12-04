//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Graph {
private:
    int V; // Number of vertices
    int E; // Number of edges
    std::vector<std::vector<int>> adj; // Adjacency list

public:
    // Default Constructor
    Graph();

    // Constructor with size
    Graph(int V);

    // Initialize/Reset graph with V vertices
    void resize(int V);

    // Add an undirected edge
    void add_edge(int u, int v);

    // Load graph from a DIMACS format file
    // Returns true if successful, false otherwise
    bool load_from_file(const std::string& filename);

    // Getters
    int num_vertices() const;
    int num_edges() const;
    int degree(int v) const;
    const std::vector<int>& neighbors(int v) const;

    // Debug
    void print() const;
};

#endif //GRAPH_H