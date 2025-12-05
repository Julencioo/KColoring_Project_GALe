#include "Graph.h"
#include <iostream>  // std::istream

// Constructor: inicializa n y crea adj con n listas vacías
Graph::Graph(int n_) : n(n_), adj(n_) {
    // adj[0], adj[1], ..., adj[n-1] empiezan como vectores<int> vacíos
}

// Añade arista no dirigida (u - v)
void Graph::add_edge(int u, int v) {
    // asumimos 0 <= u, v < n
    adj[u].push_back(v);
    adj[v].push_back(u);  // no dirigido
}

// Lee un grafo no dirigido del flujo 'in' con formato:
//
// n m
// u v
// u v
// ...
Graph read_graph(std::istream &in) {
    int n, m;
    in >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        in >> u >> v;
        g.add_edge(u, v);
    }

    return g;
}