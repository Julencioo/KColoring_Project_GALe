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

#### **2.2. Algorithmic Steps**
1.  **Ordering:** The algorithm starts with an uncolored graph.
2.  **Selection:** In each step, the algorithm selects the uncolored vertex with the **highest saturation degree**.
    * *Tie-Breaking 1:* If there is a tie in saturation, pick the vertex among them with the **highest degree** (number of uncolored neighbors).
    * *Tie-Breaking 2:* If a tie persists, pick any of the tied vertices arbitrarily (e.g., the one with the lowest ID).
3.  **Assignment:** Assign the smallest valid color index ($0, 1, 2, \dots$) that does not conflict with the current neighbors.
4.  **Update:** Update the saturation degrees of the neighbors and repeat the process until all vertices are colored.

#### **2.3. Justification of Choice**
We chose DSATUR as our primary heuristic for the following reasons:
1.  **Dynamic Efficiency:** By prioritizing the "most constrained" vertices (those with the most colored neighbors), DSATUR typically finds a chromatic number much closer to the optimal $\chi(G)$ than static methods, without the exponential cost of exact algorithms.
2.  **Complexity Balance:** The theoretical time complexity of a naive implementation is $O(n^3)$, but with optimized data structures, it can approach $O(n^2)$. This allows it to scale to the large graphs (e.g., `C4000.5.col` or `k-queens`) required by our experimental dataset.
3.  **Benchmark Standard:** DSATUR is widely regarded as the standard benchmark for graph coloring heuristics. Implementing it provides a strong baseline to measure the effectiveness of our meta-heuristic (Genetic Algorithm).