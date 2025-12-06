//
// Created by YOUR_NAME (YOUR_LOGIN)
//

#include "KColorExact.h" // Usar comillas directas si CMake está bien configurado
#include <algorithm>
#include <vector>


// 1) Ordenar vértices por grado decreciente (heurística de branching)
static std::vector<int> compute_order_by_degree(const Graph &g) {
    int n = g.num_vertices();
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;

    std::sort(order.begin(), order.end(),
              [&](int a, int b) {
                  return g.degree(a) > g.degree(b);
              });
    return order;
}

// 2) ¿Podemos asignar el color c al vértice v sin conflicto?
static bool can_use_color(const Graph &g,
                          const std::vector<int> &color,
                          int v, int c) {
    for (int u : g.neighbors(v)) {
        if (color[u] == c) return false;
    }
    return true;
}

// 3) Comprobar si el vértice u tiene algún color disponible (Forward Checking)
static bool has_any_available_color(const Graph &g,
                                    const std::vector<int> &color,
                                    int u, int k) {
    for (int c = 0; c < k; ++c) {
        bool ok = true;
        for (int w : g.neighbors(u)) {
            if (color[w] == c) {
                ok = false;
                break;
            }
        }
        if (ok) return true; // Encontrado un color válido
    }
    return false; // Sin colores disponibles
}

// 4) Backtracking recursivo
static bool k_color_backtrack(const Graph &g, int k,
                              std::vector<int> &color,
                              const std::vector<int> &order,
                              int idx) {
    int n = g.num_vertices();

    if (idx == n) return true; // Caso base: todos coloreados

    int v = order[idx];

    for (int c = 0; c < k; ++c) {
        if (!can_use_color(g, color, v, c)) continue;

        color[v] = c;

        // Poda: Forward Checking
        bool dead_branch = false;
        for (int u : g.neighbors(v)) {
            if (color[u] == -1) {
                if (!has_any_available_color(g, color, u, k)) {
                    dead_branch = true;
                    break;
                }
            }
        }

        if (!dead_branch) {
            if (k_color_backtrack(g, k, color, order, idx + 1)) return true;
        }

        color[v] = -1; // Backtrack
    }

    return false;
}

// 5) Helper interno
static bool is_k_colorable(const Graph &g, int k, std::vector<int> &colors) {
    int n = g.num_vertices();
    colors.assign(n, -1);
    auto order = compute_order_by_degree(g);
    return k_color_backtrack(g, k, colors, order, 0);
}

// 6) Implementación del método público
ColoringResult KColorExact::solve(const Graph& g) {
    int n = g.num_vertices();
    if (n == 0) return {0, {}};

    std::vector<int> best_colors;

    // Probamos k desde 1 hasta n
    for (int k = 1; k <= n; ++k) {
        if (is_k_colorable(g, k, best_colors)) {
            return {k, best_colors};
        }
    }
    return {n, best_colors};
}