import os
import subprocess
import csv

GRAPHS_DIR = "graphs"
EXECUTABLE = r"cmake-build-debug\KColoring.exe"   # o la ruta a tu binario exacto
OUTPUT_CSV = "results_exact.csv"

def parse_result_line(line):
    """
    Esperamos una línea tipo:
    RESULT algo=exact n=20 m=50 chi=3 time_us=12345
    """
    parts = line.strip().split()
    data = {}
    for part in parts[1:]:  # saltamos "RESULT"
        key, value = part.split("=")
        data[key] = value
    return data

def main():
    graph_files = sorted(
        f for f in os.listdir(GRAPHS_DIR)
        if f.endswith(".txt")
    )

    with open(OUTPUT_CSV, "w", newline="") as csvfile:
        fieldnames = ["graph", "algo", "n", "m", "chi", "time_us"]
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()

        for gf in graph_files:
            path = os.path.join(GRAPHS_DIR, gf)
            print("Running on", path)

            # Llamamos al ejecutable y le pasamos el grafo por stdin
            proc = subprocess.run(
                [EXECUTABLE],
                stdin=open(path, "r"),
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )

            # Buscar la línea RESULT en stdout
            result_line = None
            for line in proc.stdout.splitlines():
                if line.startswith("RESULT"):
                    result_line = line
                    break

            if result_line is None:
                print("WARNING: no RESULT line for", gf)
                print("STDOUT:\n", proc.stdout)
                print("STDERR:\n", proc.stderr)
                continue

            data = parse_result_line(result_line)
            writer.writerow({
                "graph": gf,
                "algo": data.get("algo", "exact"),
                "n": data.get("n", ""),
                "m": data.get("m", ""),
                "chi": data.get("chi", ""),
                "time_us": data.get("time_us", ""),
            })

if __name__ == "__main__":
    main()