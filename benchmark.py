import subprocess
import glob
import os
import csv
import time

# --- CONFIGURACIÓN ---
# Ajusta esta ruta a tu ejecutable compilado.
# En CLion suele ser: "./cmake-build-debug/K_Coloring_Project_GALe"
# En Windows/VS puede ser: "./cmake-build-debug/Debug/K_Coloring_Project_GALe.exe"
EJECUTABLE = "kcoloring2.exe"
CARPETA_DATOS = "graphs"
ARCHIVO_SALIDA = "resultados_comparativa.csv"
TIMEOUT_SEG = 120  # Tiempo máximo por grafo para evitar bloqueos

def ejecutar_benchmark():
    # Verificar si el ejecutable existe
    if not os.path.exists(EJECUTABLE) and not os.path.exists(EJECUTABLE + ".exe"):
        print(f"Error: No se encuentra el ejecutable en: {EJECUTABLE}")
        print("Asegúrate de compilar el proyecto C++ primero.")
        return

    # Preparar el archivo CSV de salida
    with open(ARCHIVO_SALIDA, 'w', newline='', encoding='utf-8') as csvfile:
        columnas = ['Archivo', 'Algoritmo', 'Vertices', 'Aristas', 'Colores (k)', 'Tiempo (s)']
        writer = csv.DictWriter(csvfile, fieldnames=columnas)
        writer.writeheader()

        # Buscar todos los archivos de grafos (.col y .txt)
        archivos_grafos = glob.glob(os.path.join(CARPETA_DATOS, "*.col")) + \
                          glob.glob(os.path.join(CARPETA_DATOS, "*.txt"))
        archivos_grafos.sort()

        if not archivos_grafos:
            print(f"No se encontraron archivos en {CARPETA_DATOS}")
            return

        print(f"Iniciando pruebas en {len(archivos_grafos)} grafos...")
        print("-" * 60)

        for ruta_grafo in archivos_grafos:
            nombre_archivo = os.path.basename(ruta_grafo)
            print(f"Procesando: {nombre_archivo} ...", end=" ", flush=True)

            try:
                # Ejecutar tu programa C++: ./programa ruta_del_grafo
                inicio = time.time()
                resultado = subprocess.run(
                    [EJECUTABLE, ruta_grafo],
                    capture_output=True,
                    text=True,
                    timeout=TIMEOUT_SEG
                )

                # Analizar la salida estándar (stdout) buscando líneas "CSV_RESULT"
                lineas_procesadas = 0
                for linea in resultado.stdout.splitlines():
                    if linea.startswith("CSV_RESULT"):
                        # Formato esperado: CSV_RESULT,Algoritmo,Archivo,V,E,k,Tiempo
                        partes = linea.split(',')
                        if len(partes) >= 7:
                            row = {
                                'Archivo': partes[2],
                                'Algoritmo': partes[1],
                                'Vertices': partes[3],
                                'Aristas': partes[4],
                                'Colores (k)': partes[5],
                                'Tiempo (s)': partes[6]
                            }
                            writer.writerow(row)
                            lineas_procesadas += 1

                csvfile.flush() # Guardar cambios en disco inmediatamente
                print(f"OK ({lineas_procesadas} resultados)")

            except subprocess.TimeoutExpired:
                print("TIMEOUT (El proceso tardó demasiado)")
                # Registrar el timeout en el CSV para constancia
                writer.writerow({
                    'Archivo': nombre_archivo,
                    'Algoritmo': 'TIMEOUT_GLOBAL',
                    'Vertices': '-', 'Aristas': '-', 'Colores (k)': '-', 'Tiempo (s)': TIMEOUT_SEG
                })
            except Exception as e:
                print(f"ERROR: {e}")

    print("-" * 60)
    print(f"Benchmark finalizado. Datos guardados en {ARCHIVO_SALIDA}")

if __name__ == "__main__":
    ejecutar_benchmark()