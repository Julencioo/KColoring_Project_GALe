import subprocess
import glob
import os
import csv
import time
import sys

# --- CONFIGURATION ---
NOMBRE_EJECUTABLE = "kcoloring4.exe"
CARPETA_DATOS = "graphs"
ARCHIVO_SALIDA = "resultados_comparativa.csv"
TIMEOUT_SEG = 60

def buscar_ejecutable():
    posibles_rutas = [
        f"./cmake-build-debug/{NOMBRE_EJECUTABLE}",
        f"./cmake-build-debug/{NOMBRE_EJECUTABLE}.exe",
        f"./cmake-build-debug/Debug/{NOMBRE_EJECUTABLE}.exe",
        f"./build/{NOMBRE_EJECUTABLE}",
        f"./{NOMBRE_EJECUTABLE}"
    ]
    for ruta in posibles_rutas:
        if os.path.exists(ruta):
            return ruta
    return None

def procesar_salida(output_text, writer):
    count = 0
    for linea in output_text.splitlines():
        if linea.startswith("CSV_RESULT"):
            partes = linea.split(',')
            if len(partes) >= 7:
                row = {
                    'Archivo': partes[2],
                    'Algoritmo': partes[1],
                    'Vertices': partes[3],
                    'Aristas': partes[4],
                    'Colores (k)': partes[5],
                    'Tiempo (ns)': partes[6]  # CHANGED: Now storing nanoseconds
                }
                writer.writerow(row)
                count += 1
    return count

def ejecutar_benchmark():
    ruta_exe = buscar_ejecutable()
    if not ruta_exe:
        print(f"ERROR FATAL: No se encuentra el ejecutable '{NOMBRE_EJECUTABLE}'.")
        sys.exit(1)

    print(f"Ejecutable encontrado: {ruta_exe}")

    with open(ARCHIVO_SALIDA, 'w', newline='', encoding='utf-8') as csvfile:
        # CHANGED HEADER: 'Tiempo (ns)'
        columnas = ['Archivo', 'Algoritmo', 'Vertices', 'Aristas', 'Colores (k)', 'Tiempo (ns)']
        writer = csv.DictWriter(csvfile, fieldnames=columnas)
        writer.writeheader()

        archivos = glob.glob(os.path.join(CARPETA_DATOS, "*.col")) + \
                   glob.glob(os.path.join(CARPETA_DATOS, "*.txt"))
        archivos.sort()

        if not archivos:
            print(f"No se encontraron archivos en '{CARPETA_DATOS}'")
            return

        print(f"Procesando {len(archivos)} grafos...")
        print("-" * 60)

        for ruta in archivos:
            nombre = os.path.basename(ruta)
            print(f"--> {nombre} ... ", end="", flush=True)

            try:
                resultado = subprocess.run(
                    [ruta_exe, ruta],
                    capture_output=True,
                    text=True,
                    timeout=TIMEOUT_SEG
                )

                n = procesar_salida(resultado.stdout, writer)
                csvfile.flush()
                if n == 0:
                    print("SIN DATOS")
                else:
                    print(f"OK ({n} algos)")

            except subprocess.TimeoutExpired as e:
                print(f"TIMEOUT ({TIMEOUT_SEG}s)", end=" ")
                texto_parcial = e.stdout if e.stdout else ""
                n = procesar_salida(texto_parcial, writer)

                writer.writerow({
                    'Archivo': nombre,
                    'Algoritmo': 'EXACT_TIMEOUT',
                    'Vertices': '-', 'Aristas': '-', 'Colores (k)': '-',
                    'Tiempo (ns)': f">{TIMEOUT_SEG*1e9}" # Approximate ns for timeout
                })
                print(f"- Datos recuperados: {n}")

            except Exception as ex:
                print(f"ERROR SISTEMA: {ex}")

    print("-" * 60)
    print(f"Resultados guardados en: {ARCHIVO_SALIDA}")

if __name__ == "__main__":
    ejecutar_benchmark()