#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iosfwd>  // std::istream

// Grafo NO dirigido
class Graph {
public:
    int n;  // número de vértices (0..n-1)
    std::vector<std::vector<int>> adj;  // listas de adyacencia

    // Constructor: crea grafo con n vértices y sin aristas
    explicit Graph(int n_);

    // Añadir arista NO dirigida (u - v)
    void add_edge(int u, int v);

    // Número de vértices (azúcar sintáctico)
    int num_vertices() const { return n; }

    // Vecinos de v (versión solo lectura)
    const std::vector<int>& neighbors(int v) const { return adj[v]; }

    // Grado de v
    int degree(int v) const { return static_cast<int>(adj[v].size()); }
};

// Función libre para leer un grafo de un flujo (stdin, archivo…)
Graph read_graph(std::istream &in);

#endif // GRAPH_H