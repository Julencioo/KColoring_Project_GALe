import os
import subprocess
import csv
import time
import glob

# --- CONFIGURATION ---
# We use the manually compiled executable name from Step 1
EXE_NAME = "kcoloring_manual"
DATA_FOLDER = "graphs"
RESULTS_FILE = "results_manual.csv"
TIMEOUT_SEC = 60

def run_benchmark():
    # 1. Detect Executable
    exe_path = f"./{EXE_NAME}"
    if os.name == 'nt':
        exe_path += ".exe"

    if not os.path.isfile(exe_path):
        print(f"CRITICAL ERROR: Could not find '{exe_path}'")
        print("Did you run the manual compilation command in the terminal?")
        print("Command: g++ -I./include src/*.cpp -o kcoloring_manual")
        return

    # 2. Find Graphs
    graph_files = glob.glob(os.path.join(DATA_FOLDER, "*.col")) + \
                  glob.glob(os.path.join(DATA_FOLDER, "*.txt"))
    graph_files.sort()

    print(f"Found {len(graph_files)} graphs. Running benchmark on '{exe_path}'...")

    # 3. Run
    with open(RESULTS_FILE, 'w', newline='') as csv_file:
        fieldnames = ["Graph", "Vertices", "Edges", "Chrom_Number", "Time_Sec", "Status"]
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()

        for graph in graph_files:
            print(f"Processing {os.path.basename(graph)}...", end=" ", flush=True)

            try:
                result = subprocess.run(
                    [exe_path, graph],
                    capture_output=True,
                    text=True,
                    timeout=TIMEOUT_SEC
                )

                if result.returncode != 0:
                    print("ERROR (Runtime Crash)")
                    writer.writerow({"Graph": os.path.basename(graph), "Status": "Crash"})
                    continue

                # Parse Output
                parsed = False
                for line in result.stdout.splitlines():
                    if line.startswith("CSV_RESULT"):
                        parts = line.strip().split(',')
                        if len(parts) >= 6:
                            writer.writerow({
                                "Graph": parts[2],
                                "Vertices": parts[3],
                                "Edges": parts[4],
                                "Chrom_Number": parts[5],
                                "Time_Sec": parts[6],
                                "Status": "Success"
                            })
                            print(f"OK (k={parts[5]}, t={parts[6]}s)")
                            parsed = True
                            break

                if not parsed:
                    print("ERROR (No valid output)")

            except subprocess.TimeoutExpired:
                print("TIMEOUT")
                writer.writerow({"Graph": os.path.basename(graph), "Status": "Timeout"})
            except Exception as e:
                print(f"EXCEPTION: {e}")

if __name__ == "__main__":
    run_benchmark()