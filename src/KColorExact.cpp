#include "KColorExact.h"
#include <algorithm>  // std::sort

// 1) Ordenar vértices por grado decreciente (heurística de branching)
static std::vector<int> compute_order_by_degree(const Graph &g) {
    int n = g.n;
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;

    std::sort(order.begin(), order.end(),
              [&](int a, int b) {
                  return g.adj[a].size() > g.adj[b].size();
              });
    return order;
}

// 2) ¿Podemos asignar el color c al vértice v sin conflicto
// con los vecinos YA coloreados?
static bool can_use_color(const Graph &g,
                          const std::vector<int> &color,
                          int v, int c) {
    for (int u : g.adj[v]) {
        if (color[u] == c) return false;  // vecino con mismo color
    }
    return true;
}

// 3) NUEVO: ¿el vértice u tiene ALGÚN color disponible en [0..k-1]
// que no choque con los vecinos ya coloreados?
static bool has_any_available_color(const Graph &g,
                                    const std::vector<int> &color,
                                    int u, int k) {
    // probamos todos los colores posibles para u
    for (int c = 0; c < k; ++c) {
        bool ok = true;
        for (int w : g.adj[u]) {
            if (color[w] == c) {
                ok = false;   // este color está bloqueado por un vecino
                break;
            }
        }
        if (ok) {
            // hemos encontrado al menos un color posible para u
            return true;
        }
    }
    // ningún color sirve -> u está "muerto"
    return false;
}

// 4) Backtracking recursivo con poda extra (forward checking)
static bool k_color_backtrack(const Graph &g, int k,
                              std::vector<int> &color,
                              const std::vector<int> &order,
                              int idx) {
    int n = g.n;

    // Caso base: todos los vértices coloreados
    if (idx == n) {
        return true;
    }

    int v = order[idx];  // vértice que vamos a colorear ahora

    // Probar todos los colores posibles [0..k-1]
    for (int c = 0; c < k; ++c) {
        if (!can_use_color(g, color, v, c)) continue;

        // Asignamos color a v
        color[v] = c;

        // --- PODA NUEVA: comprobamos vecinos no coloreados ---
        bool dead_branch = false;
        for (int u : g.adj[v]) {
            if (color[u] == -1) {
                // si algún vecino u ya no tiene ningún color disponible, rama muerta
                if (!has_any_available_color(g, color, u, k)) {
                    dead_branch = true;
                    break;
                }
            }
        }

        if (!dead_branch) {
            // solo seguimos si la asignación no mata a ningún vecino
            if (k_color_backtrack(g, k, color, order, idx + 1)) {
                return true;  // solución encontrada en esta rama
            }
        }

        // Deshacemos asignación (backtrack)
        color[v] = -1;
    }

    // Ningún color funciona para este vértice -> no hay solución en esta rama
    return false;
}

// 5) Función pública: ¿es k-colorable?
bool is_k_colorable(const Graph &g, int k, std::vector<int> &colors) {
    int n = g.n;
    colors.assign(n, -1);                 // todos sin color
    auto order = compute_order_by_degree(g);  // heurística de ordenación

    return k_color_backtrack(g, k, colors, order, 0);
}

// 6) Función pública: buscar el k mínimo (número cromático)
int chromatic_number(const Graph &g, std::vector<int> &best_colors) {
    int n = g.n;

    std::vector<int> colors;

    // probamos k desde 1 hasta n (cota superior trivial)
    for (int k = 1; k <= n; ++k) {
        if (is_k_colorable(g, k, colors)) {
            best_colors = colors;
            return k;
        }
    }

    // teóricamente no deberíamos llegar aquí
    return -1;
}