#include <iostream>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "KColorExact.h"

int main() {
    Graph g = read_graph(std::cin);

    std::vector<int> colors;
    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();
    int k = chromatic_number(g, colors);
    auto end = Clock::now();

    auto elapsed_us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // (Opcional: imprimir algo bonito para humanos)
    std::cout << "Chromatic number = " << k << "\n";
    std::cout << "Execution time: " << elapsed_us << " microseconds\n";

    // ⚠️ ESTA LÍNEA ES LA IMPORTANTE PARA PYTHON:
    std::cout << "RESULT"
              << " algo=exact"
              << " n=" << g.n
              << " chromatic=" << k
              << " time_us=" << elapsed_us
              << "\n";

    return 0;
}