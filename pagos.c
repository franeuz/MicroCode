#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PERSONAS 10
#define MAX_NOMBRE 50
#define MAX_NOTA 100

typedef struct {
    char nombre[MAX_NOMBRE];
    char fecha[11]; // Formato DD/MM/YYYY
    float monto;
    float deuda;
    char nota[MAX_NOTA];
} Pago;

void obtenerFechaActual(char *fecha) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void registrarPago() {
    FILE *archivo = fopen("pagos.dat", "ab");
    if (!archivo) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Pago p;
    char fechaInput[20];

    printf("\n--- Registrar Pago ---\n");
    printf("Nombre: ");
    fgets(p.nombre, MAX_NOMBRE, stdin);
    p.nombre[strcspn(p.nombre, "\n")] = 0;

    printf("Fecha (DD/MM/YYYY) [Enter para usar fecha actual]: ");
    fgets(fechaInput, 20, stdin);
    fechaInput[strcspn(fechaInput, "\n")] = 0;
    if (strlen(fechaInput) == 0) {
        obtenerFechaActual(p.fecha);
    } else {
        strncpy(p.fecha, fechaInput, 10);
        p.fecha[10] = '\0';
    }

    printf("Monto abonado: ");
    scanf("%f", &p.monto);
    getchar(); // limpiar buffer

    printf("Deuda restante: ");
    scanf("%f", &p.deuda);
    getchar();

    printf("Nota (opcional): ");
    fgets(p.nota, MAX_NOTA, stdin);
    p.nota[strcspn(p.nota, "\n")] = 0;

    fwrite(&p, sizeof(Pago), 1, archivo);
    fclose(archivo);

    printf("\nPago registrado exitosamente.\n");
}

void mostrarHistorial() {
    FILE *archivo = fopen("pagos.dat", "rb");
    if (!archivo) {
        printf("No hay historial registrado.\n");
        return;
    }

    Pago p;
    printf("\n--- Historial de Pagos ---\n");
    printf("%-20s %-12s %-10s %-10s %-20s\n", "Nombre", "Fecha", "Monto", "Deuda", "Nota");
    printf("-------------------------------------------------------------------------------\n");

    while (fread(&p, sizeof(Pago), 1, archivo)) {
        printf("%-20s %-12s %-10.2f %-10.2f %-20s\n",
               p.nombre, p.fecha, p.monto, p.deuda, p.nota);
    }

    fclose(archivo);
}

void menu() {
    int opcion;
    do {
        printf("\n=====================================\n");
        printf("  ADMINISTRADOR DE PAGOS - MENU\n");
        printf("=====================================\n");
        printf("1. Registrar pago\n");
        printf("2. Mostrar historial de pagos\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: registrarPago(); break;
            case 2: mostrarHistorial(); break;
            case 3: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 3);
}

int main() {
    menu();
    return 0;
}

