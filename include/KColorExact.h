#ifndef KCOLOREXACT_H
#define KCOLOREXACT_H

#include <vector>
#include "Graph.h"

// Devuelve true si g es k-colorable y escribe la coloración en 'colors'.
bool is_k_colorable(const Graph &g, int k, std::vector<int> &colors);

// Calcula el número cromático buscándolo desde k=1 en adelante.
// Devuelve el k mínimo tal que g es k-colorable, y deja la coloración en 'best_colors'.
// Devuelve -1 solo si algo va MUY mal (en teoría no debería ocurrir).
int chromatic_number(const Graph &g, std::vector<int> &best_colors);

#endif // KCOLOREXACT_H