#include <iostream>
#include "Graph.h"

int main() {
    // Creamos un grafo con 4 vértices: 0,1,2,3
    Graph g(4);

    // Añadimos algunas aristas: 0-1, 0-2, 1-3
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);

    std::cout << "Graph has " << g.num_vertices() << " vertices.\n";

    // Imprimimos la lista de adyacencias
    for (int v = 0; v < g.num_vertices(); ++v) {
        std::cout << "Neighbors of " << v << ": ";
        for (int u : g.neighbors(v)) {
            std::cout << u << " ";
        }
        std::cout << "\n";
    }

    return 0;
}