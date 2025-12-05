//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include "../include/Graph.h"
#include <algorithm> // For std::max

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
    // Safety check to ensure we don't access out of bounds
    if (u >= 0 && u < V && v >= 0 && v < V) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        E++;
    }
}

// DIMACS Loader (.col)
bool Graph::load_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        char type;
        ss >> type;

        if (type == 'c') continue;
        else if (type == 'p') {
            std::string format;
            int num_v, num_e;
            ss >> format >> num_v >> num_e;
            resize(num_v);
        } else if (type == 'e') {
            int u, v;
            ss >> u >> v;
            add_edge(u - 1, v - 1);
        }
    }
    infile.close();
    return true;
}

// TXT Loader (Simple Edge List)
bool Graph::load_from_file2(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::vector<std::pair<int, int>> edge_list;
    int max_node_id = 0;
    std::string line;

    // Pass 1: Read edges and find the maximum vertex ID
    while (std::getline(infile, line)) {
        // Skip comments or empty lines
        if (line.empty() || line[0] == '#' || line[0] == 'c') continue;

        std::stringstream ss(line);
        int u, v;
        if (ss >> u >> v) {
            edge_list.push_back({u, v});
            if (u > max_node_id) max_node_id = u;
            if (v > max_node_id) max_node_id = v;
        }
    }
    infile.close();

    if (edge_list.empty()) {
        std::cerr << "Warning: No edges found in " << filename << "\n";
        return false;
    }

    // Pass 2: Resize and add edges
    // We assume vertices are 0-indexed or 1-indexed.
    // We resize to max_id + 1 to accommodate the largest index.
    resize(max_node_id + 1);

    for (const auto& edge : edge_list) {
        // Here we assume raw indices from TXT (0-based or 1-based mixed)
        // If your TXT is strictly 1-based, you might want to do edge.first - 1
        // But for generic TXT, keeping the raw index is usually safer unless you see node 0 unused.
        // If the file is 1-based, index 0 will just be an isolated vertex (harmless).
        add_edge(edge.first, edge.second);
    }

    return true;
}

int Graph::num_vertices() const { return V; }
int Graph::num_edges() const { return E; }

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