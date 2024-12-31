#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Implementación de ejemplo de dataRead
int dataRead(uint8_t *buffer, uint32_t size, uint8_t *source, uint32_t sourceSize) {
    if (buffer == NULL || source == NULL || size == 0) {
        return -1; // Código de error: entrada inválida
    }

    if (size > sourceSize) {
        return -2; // Código de error: tamaño solicitado excede el origen
    }

    memcpy(buffer, source, size); // Copiar datos al buffer
    return 0; // Operación exitosa
}

void test_dataRead() {
    uint8_t sourceData[] = {0x10, 0x20, 0x30, 0x40, 0x50}; // Datos de origen
    uint8_t buffer[10]; // Buffer para almacenar datos leídos
    int result;

    printf("=== Comenzando pruebas para dataRead ===\n");

    // Caso 1: Leer correctamente datos
    result = dataRead(buffer, 3, sourceData, sizeof(sourceData));
    if (result == 0 && buffer[0] == 0x10 && buffer[1] == 0x20 && buffer[2] == 0x30) {
        printf("Prueba 1 exitosa: datos leídos correctamente.\n");
    } else {
        printf("Prueba 1 fallida: datos incorrectos o error en el resultado.\n");
    }

    // Caso 2: Buffer nulo
    result = dataRead(NULL, 3, sourceData, sizeof(sourceData));
    if (result == -1) {
        printf("Prueba 2 exitosa: error detectado para buffer nulo.\n");
    } else {
        printf("Prueba 2 fallida: no se detectó error para buffer nulo.\n");
    }

    // Caso 3: Tamaño solicitado mayor al origen
    result = dataRead(buffer, 10, sourceData, sizeof(sourceData));
    if (result == -2) {
        printf("Prueba 3 exitosa: error detectado para tamaño mayor al origen.\n");
    } else {
        printf("Prueba 3 fallida: no se detectó error para tamaño mayor al origen.\n");
    }

    // Caso 4: Datos de origen nulos
    result = dataRead(buffer, 3, NULL, sizeof(sourceData));
    if (result == -1) {
        printf("Prueba 4 exitosa: error detectado para datos de origen nulos.\n");
    } else {
        printf("Prueba 4 fallida: no se detectó error para datos de origen nulos.\n");
    }

    printf("=== Fin de las pruebas para dataRead ===\n");
}

int main() {
    test_dataRead();
    return 0;
}
