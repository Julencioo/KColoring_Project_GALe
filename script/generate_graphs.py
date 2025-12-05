import os
import networkx as nx

OUTPUT_DIR = "graphs"

def save_graph(G, filename):
    # Asegurar que los nodos están en 0..n-1
    mapping = {node: i for i, node in enumerate(G.nodes())}
    G = nx.relabel_nodes(G, mapping)

    n = G.number_of_nodes()
    edges = list(G.edges())
    m = len(edges)

    with open(filename, "w") as f:
        f.write(f"{n} {m}\n")
        for u, v in edges:
            f.write(f"{u} {v}\n")

def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    ns = [20, 30, 40, 50]
    ps = [0.1, 0.2, 0.3]
    repeats = 3

    graph_id = 1

    for n in ns:
        for p in ps:
            for r in range(repeats):
                G = nx.gnp_random_graph(n, p)  # no dirigido
                filename = os.path.join(
                    OUTPUT_DIR,
                    f"g_{graph_id:02d}_n{n}_p{p:.1f}_r{r}.txt"
                )
                save_graph(G, filename)
                print("Generated:", filename)
                graph_id += 1

if __name__ == "__main__":
    main()