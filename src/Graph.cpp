//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include "Graph.h"

Graph::Graph() : V(0), E(0) {}

Graph::Graph(int V) : V(V), E(0) {
    adj.resize(V);
}

void Graph::resize(int new_V) {
    this->V = new_V;
    this->E = 0;
    adj.clear();
    adj.resize(new_V);
}

void Graph::add_edge(int u, int v) {
    if (u >= 0 && u < V && v >= 0 && v < V) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        E++;
    }
}

bool Graph::load_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        std::stringstream ss(line);
        char type;
        ss >> type;

        if (type == 'c') {
            // Comment line, skip
            continue;
        } else if (type == 'p') {
            // Problem line: p edge V E
            std::string format;
            int num_v, num_e;
            ss >> format >> num_v >> num_e;
            resize(num_v);
            // Optional: You could reserve memory here if needed
            // std::cout << "Loading graph: " << num_v << " vertices, " << num_e << " edges expected.\n";
        } else if (type == 'e') {
            // Edge line: e u v
            int u, v;
            ss >> u >> v;
            // DIMACS is usually 1-indexed, convert to 0-indexed
            add_edge(u - 1, v - 1);
        }
    }

    infile.close();
    return true;
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
    std::cout << "Graph (V=" << V << ", E=" << E << "):\n";
    for (int v = 0; v < V; ++v) {
        std::cout << v << ": ";
        for (int neighbor : adj[v]) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}