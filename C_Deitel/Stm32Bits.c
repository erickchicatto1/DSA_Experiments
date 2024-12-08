#include <stdio.h>
#include <stdint.h>

// Función para simular PCA9685_SetBit
void PCA9685_SetBit(uint8_t *Register, uint8_t Bit, uint8_t Value) {
    uint8_t readValue = *Register; // Leer el valor actual del registro
    uint8_t bitArray[8];

    // Extraer cada bit del registro actual
    for (uint8_t i = 0; i < 8; i++) {
        bitArray[i] = (readValue >> i) & 1;
    }

    // Mostrar los bits originales
    printf("Bits originales: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", bitArray[i]);
    }
    printf("\n");

    // Modificar el bit especificado
    if (Value == 0) {
        readValue &= ~(1 << Bit); // Poner a 0 el bit
    } else {
        readValue |= (1 << Bit);  // Poner a 1 el bit
    }

    // Actualizar el registro con el nuevo valor
    *Register = readValue;

    // Extraer los bits nuevamente para verificar el cambio
    for (uint8_t i = 0; i < 8; i++) {
        bitArray[i] = (readValue >> i) & 1;
    }

    // Mostrar los bits modificados
    printf("Bits modificados: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", bitArray[i]);
    }
    printf("\n");
}

// Programa principal para probar la función
int main() {
    uint8_t Register = 0b11010101; // Registro inicial (ejemplo)
    uint8_t BitToModify = 3;       // Bit que queremos modificar (posición 3)
    uint8_t NewValue = 1;          // Nuevo valor del bit (1 o 0)

    printf("Valor inicial del registro: 0x%02X\n", Register);
    PCA9685_SetBit(&Register, BitToModify, NewValue);
    printf("Valor final del registro: 0x%02X\n", Register);

    return 0;
}