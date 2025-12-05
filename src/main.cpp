#include <iostream>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "KColorExact.h"

int main() {
    using Clock = std::chrono::steady_clock;

    // Leer grafo desde stdin
    Graph g = read_graph(std::cin);

    std::vector<int> colors;

    auto start = Clock::now();
    int k = chromatic_number(g, colors);
    auto end = Clock::now();

    auto elapsed_us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // *** LÍNEA QUE TIENE QUE SALIR SÍ O SÍ ***
    std::cout << "RESULT"
              << " algo=exact"
              << " n=" << g.n
              << " chromatic=" << k
              << " time_us=" << elapsed_us
              << "\n";

    return 0;
}