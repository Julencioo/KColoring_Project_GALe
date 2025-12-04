# Brno University of Technology
## Faculty of Information Technology

**Course:** Graph Algorithms and Optimization (GALe)
**Project Topic 13:** Comparison - Graph Coloring

---

# **Project Documentation**

**Authors:**
* **Eduardo Martín Postigo** (xmartie01)
* **Julen Mendoza Borrero** (xmendo00) **Date:** December 4, 2025

---

## **Index**
1.  [Introduction](#1-introduction)
    * 1.1 Problem Statement
    * 1.2 Complexity and Motivation
    * 1.3 Project Objective
2.  [Algorithm Analysis: DSATUR](#2-algorithm-analysis-dsatur)
    * 2.1 Principle of the Algorithm
    * 2.2 Algorithmic Steps
    * 2.3 Justification of Choice

---

### **1. Introduction**

#### **1.1. Problem Statement**
The Graph Coloring Problem (GCP), specifically Vertex Coloring, is a fundamental problem in graph theory and combinatorial optimization. The objective is to assign a color (an integer value) to each vertex of a graph $G = (V, E)$ such that no two adjacent vertices share the same color. The primary goal is to minimize the number of colors used, known as the chromatic number $\chi(G)$ or $k$.

Formally, a $k$-coloring of a graph $G$ is a function $c: V \to \{1, 2, \dots, k\}$ such that for every edge $(u, v) \in E$, $c(u) \neq c(v)$.

#### **1.2. Complexity and Motivation**
Determining the chromatic number of a graph is known to be an **NP-Hard** problem. Exact algorithms can find the optimal $\chi(G)$ but generally exhibit exponential time complexity, making them computationally intractable for large, dense graphs. Consequently, heuristic and approximation algorithms are essential for solving practical instances where a "good enough" solution is required in polynomial time.



[Image of graph coloring problem]


#### **1.3. Project Objective**
This project aims to analyze and compare the performance of three distinct algorithmic approaches to the $k$-coloring problem:

1.  **DSATUR (Degree of Saturation):** A sequential heuristic that dynamically orders vertices to improve solution quality over standard greedy methods.
2.  **Backtracking (Exact):** A brute-force approach that guarantees finding the optimal chromatic number $\chi(G)$, serving as a baseline for accuracy on smaller graphs.
3.  **Genetic Algorithm (Meta-heuristic):** An evolutionary approach designed to explore the solution space more broadly, aiming to overcome local optima in larger or more complex graph instances.

We will benchmark these algorithms on a dataset of over 30 graphs to evaluate the trade-offs between execution time and solution quality (minimizing $k$).

---

### **2. Algorithm Analysis: DSATUR**

#### **2.1. Principle of the Algorithm**
**DSATUR** (Degree of Saturation), proposed by Daniel Brélaz in 1979, is a sequential greedy heuristic. Unlike simple greedy algorithms that color vertices in a static, pre-calculated order (e.g., random or decreasing degree), DSATUR dynamically selects the next vertex to color based on the state of the current partial coloring.

The core heuristic is based on the **saturation degree** of a vertex, defined as the number of *different* colors currently assigned to its adjacent neighbors. By prioritizing vertices with high saturation, the algorithm handles the most constrained parts of the graph first.

#### **2.2. Algorithmic Steps (Pseudocode)**

The following pseudocode describes our specific implementation of the DSATUR heuristic, detailing the priority selection criteria (Saturation Degree followed by Vertex Degree as a tie-breaker).

```text
Algorithm DSATUR(Graph G):
    Input: A graph G = (V, E)
    Output: A valid coloring assignment for all vertices in V

    // 1. Initialization
    // Complexity: O(V) - We iterate through all vertices once to initialize structures.
    Let assignment[v] = -1 for all v in V                 
    Let saturation[v] = {} (empty RB-Tree/Set) for all v in V
    Let degree[v] = deg(v) for all v in V
    Let uncolored_count = |V|

    // 2. Main Loop
    // Complexity: The loop runs exactly |V| times (once for each vertex).
    While uncolored_count > 0:
        
        // --- Selection Heuristic ---
        // Complexity: O(V) per iteration
        // In this implementation, we linearly scan all vertices to find the best candidate.
        best_vertex = null
        max_sat = -1
        max_deg = -1

        For each vertex v in V:
            If assignment[v] == -1:
                current_sat = size(saturation[v])  // O(1) for std::set size
                current_deg = degree[v]

                // Primary Criteria: Maximum Saturation Degree
                If current_sat > max_sat:
                    best_vertex = v
                    max_sat = current_sat
                    max_deg = current_deg
                
                // Secondary Criteria (Tie-Breaker): Maximum Degree
                Else If current_sat == max_sat:
                    If current_deg > max_deg:
                        best_vertex = v
                        max_sat = current_sat
                        max_deg = current_deg
        
        // --- Assignment ---
        // Complexity: O(k * log(Delta)) 
        // We check colors 0, 1... until valid. 'k' is the chromatic number found so far.
        // Checking existence in std::set is O(log(current_saturation)).
        color = 0
        While color in saturation[best_vertex]:
            color = color + 1
        
        assignment[best_vertex] = color
        uncolored_count = uncolored_count - 1

        // --- Update Neighbors ---
        // Complexity: O(deg(best_vertex) * log(Delta))
        // We update saturation for all uncolored neighbors. 
        // Insertion into std::set is logarithmic with respect to the number of colors.
        For each neighbor u of best_vertex:
            If assignment[u] == -1:
                Add color to saturation[u]

    Return assignment
```
The total complexity is the sum of the complexities of its dominant parts.

$$O(\text{Total}) = O(V^2 + E \log V)$$

* The term **$O(V^2)$** arises from the linear search for the vertex with the highest saturation degree in each of the $V$ steps.
* The term **$O(E \log V)$** arises from updating the saturation set of neighbors throughout the execution of the algorithm.

This complexity, which lies between $O(V^2)$ (for sparse graphs) and $O(V^2 \log V)$ (for dense graphs where $E \approx V^2$), 
demonstrates why DSATUR is an **efficient heuristic algorithm** and significantly faster than an exact algorithm like **Backtracking** (which is exponential).
#### **2.3. Justification of Choice**
We chose DSATUR as our primary heuristic for the following reasons:
1.  **Dynamic Efficiency:** By prioritizing the "most constrained" vertices (those with the most colored neighbors), DSATUR typically finds a chromatic number much closer to the optimal $\chi(G)$ than static methods, without the exponential cost of exact algorithms.
2.  **Complexity Balance:** The theoretical time complexity of a naive implementation is $O(n^3)$, but with optimized data structures, it can approach $O(n^2)$. This allows it to scale to the large graphs (e.g., `C4000.5.col` or `k-queens`) required by our experimental dataset.
3.  **Benchmark Standard:** DSATUR is widely regarded as the standard benchmark for graph coloring heuristics. Implementing it provides a strong baseline to measure the effectiveness of our meta-heuristic (Genetic Algorithm).