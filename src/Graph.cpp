//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include "Graph.h"

Graph::Graph(int V) : V(V), E(0) {
    adj.resize(V);
}

void Graph::add_edge(int u, int v) {
    // Check bounds
    if (u >= 0 && u < V && v >= 0 && v < V) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
        E++;
    }
}

int Graph::num_vertices() const {
    return V;
}

int Graph::num_edges() const {
    return E;
}

int Graph::degree(int v) const {
    if (v >= 0 && v < V) {
        return (int)adj[v].size();
    }
    return 0;
}

const std::vector<int>& Graph::neighbors(int v) const {
    return adj[v];
}

void Graph::print() const {
    for (int v = 0; v < V; ++v) {
        std::cout << v << ": ";
        for (int neighbor : adj[v]) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}