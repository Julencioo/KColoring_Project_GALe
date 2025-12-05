#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iosfwd>  // forward declaration de std::istream

// Grafo NO dirigido, simple
class Graph {
public:
    int n;  // número de vértices (0..n-1)
    std::vector<std::vector<int>> adj;  // listas de adyacencia

    // Constructor: crea grafo con n vértices y sin aristas
    explicit Graph(int n_);

    // Añadir arista NO dirigida (u - v)
    void add_edge(int u, int v);

    // Helpers opcionales (por comodidad en main y algoritmos):
    int num_vertices() const { return n; }

    const std::vector<int>& neighbors(int v) const { return adj[v]; }

    int degree(int v) const { return static_cast<int>(adj[v].size()); }
};

// Lee un grafo no dirigido desde un flujo (stdin, archivo, etc.)
// Formato de entrada esperado:
//
//   n m
//   u1 v1
//   u2 v2
//   ...
//   um vm
//
// donde n = nº de vértices, m = nº de aristas,
// y cada (u, v) es una arista no dirigida entre 0 <= u, v < n.
Graph read_graph(std::istream &in);

#endif // GRAPH_H