from datetime import datetime
import os

# =============================
# FUNCIONES
# =============================

def leer_fecha_inicio(archivo="fecha_inicio.txt"):
    """Lee la fecha de inicio desde el archivo, o la pide si no existe."""
    if not os.path.exists(archivo):
        fecha = input("👉 Ingresa tu fecha de inicio (AAAA-MM-DD): ")
        with open(archivo, "w") as f:
            f.write(fecha.strip())
        return fecha.strip()
    else:
        with open(archivo, "r") as f:
            return f.read().strip()

def calcular_dias(fecha_str):
    """Calcula los días desde la fecha de inicio."""
    inicio = datetime.strptime(fecha_str, "%Y-%m-%d").date()
    hoy = datetime.today().date()
    return (hoy - inicio).days

def motivacion(dias):
    """Devuelve un mensaje según el progreso."""
    if dias < 7:
        return "¡Buen comienzo! Mantente firme 💪"
    elif dias < 30:
        return "¡Casi un mes, excelente disciplina 🚀!"
    elif dias < 90:
        return "¡3 meses de progreso, eres imparable 🔥!"
    else:
        return "¡Más allá de los 90 días, una nueva vida 🌟!"

# =============================
# PROGRAMA PRINCIPAL
# =============================

if __name__ == "__main__":
    fecha_inicio = leer_fecha_inicio()
    dias = calcular_dias(fecha_inicio)

    print("==========================================")
    print("        CONTADOR NOFAP 🚀🔥")
    print("==========================================")
    print(f"Fecha de inicio: {fecha_inicio}")
    print(f"Días transcurridos: {dias} ✅")
    print(motivacion(dias))
    print("==========================================")

