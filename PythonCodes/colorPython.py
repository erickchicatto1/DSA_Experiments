# Primary colors
RED = "#FF0000"
YELLOW = "#FFFF00"
BLUE = "#0000FF"
 # Secondary colors
ORANGE = "#FFA500"
GREEN = "#008000"
VIOLET = "#EE82EE"
 # Neutral colors
BLACK = "#000000"
GRAY = "#808080"
WHITE = "#FFFFFF"


def _tohex(value):
    #Convert an integer to a 8-bit (2 - digit ) hexadecimal string 
    if value <=0:
        return "00"
    if value >= 255:
        return "FF"
    return format(value,"02X")


#How it works?

'''
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función para convertir de decimal a hexadecimal
void decimal_a_hexadecimal(int num) {
    printf("El número en hexadecimal es: %X\n", num); // %X muestra en formato hexadecimal
}

// Función para convertir de hexadecimal a decimal
int hexadecimal_a_decimal(char hex[]) {
    int decimal = 0, base = 1, len;
    len = strlen(hex);
    
    // Recorremos el string desde el último carácter
    for (int i = len - 1; i >= 0; i--) {
        // Si el carácter es un número
        if (hex[i] >= '0' && hex[i] <= '9') {
            decimal += (hex[i] - '0') * base;
        }
        // Si el carácter es una letra (A-F o a-f)
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            decimal += (hex[i] - 'A' + 10) * base;
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f') {
            decimal += (hex[i] - 'a' + 10) * base;
        }
        base *= 16; // Aumentamos la base
    }

    return decimal;
}

int main() {
    int opcion;
    char hex[100];
    int decimal;

    printf("Conversor entre Decimal y Hexadecimal\n");
    printf("1. Decimal a Hexadecimal\n");
    printf("2. Hexadecimal a Decimal\n");
    printf("Elija una opción (1 o 2): ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        printf("Introduzca un número decimal: ");
        scanf("%d", &decimal);
        decimal_a_hexadecimal(decimal);
    }
    else if (opcion == 2) {
        printf("Introduzca un número hexadecimal (sin 0x al inicio): ");
        scanf("%s", hex);

        // Convertimos el string hexadecimal a mayúsculas para evitar errores
        for (int i = 0; hex[i]; i++) {
            hex[i] = toupper(hex[i]);
        }

        int result = hexadecimal_a_decimal(hex);
        printf("El número en decimal es: %d\n", result);
    }
    else {
        printf("Opción no válida. Por favor, elija 1 o 2.\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Función para convertir de decimal a binario
void decimal_a_binario(int num) {
    if (num == 0) {
        printf("El número en binario es: 0\n");
        return;
    }
    
    // Usamos un arreglo para almacenar el binario
    int binario[32];  // Un entero tiene como máximo 32 bits en la mayoría de las arquitecturas
    int i = 0;
    
    while (num > 0) {
        binario[i] = num % 2;  // Guardamos el resto de la división entre 2 (el bit más bajo)
        num = num / 2;  // Dividimos el número entre 2
        i++;
    }

    // Imprimimos el binario de forma correcta
    printf("El número en binario es: ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binario[j]);
    }
    printf("\n");
}

// Función para convertir de binario a decimal
int binario_a_decimal(char bin[]) {
    int decimal = 0;
    int base = 1;
    int len = strlen(bin);
    
    // Recorremos el string binario desde el último carácter
    for (int i = len - 1; i >= 0; i--) {
        // Si es '1', sumamos el valor correspondiente a la posición
        if (bin[i] == '1') {
            decimal += base;
        }
        base *= 2; // Multiplicamos la base por 2 para la siguiente posición
    }

    return decimal;
}

int main() {
    int opcion;
    char bin[100];
    int decimal;

    printf("Conversor entre Decimal y Binario\n");
    printf("1. Decimal a Binario\n");
    printf("2. Binario a Decimal\n");
    printf("Elija una opción (1 o 2): ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        printf("Introduzca un número decimal: ");
        scanf("%d", &decimal);
        decimal_a_binario(decimal);
    }
    else if (opcion == 2) {
        printf("Introduzca un número binario (sin espacios): ");
        scanf("%s", bin);
        
        // Verificar si el número binario es válido
        int valido = 1;
        for (int i = 0; bin[i] != '\0'; i++) {
            if (bin[i] != '0' && bin[i] != '1') {
                valido = 0;
                break;
            }
        }
        
        if (valido) {
            int result = binario_a_decimal(bin);
            printf("El número en decimal es: %d\n", result);
        } else {
            printf("Número binario inválido. Asegúrese de que solo contenga 0s y 1s.\n");
        }
    }
    else {
        printf("Opción no válida. Por favor, elija 1 o 2.\n");
    }

    return 0;
}



'''
 
 
 