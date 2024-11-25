#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void decimal_a_hexadecimal(int num);
int hexadecimal_a_decimal(char hex[]);



int main(){

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
        for (int i = 0; hex[i]; i++) { // Pensar en que se le tiene que hacer a este array 
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


int hexadecimal_a_decimal(char hex[]){

int decimal = 0 , base = 1 , len;
len = strlen(hex);

/*Recorremos el string desde el ultimo caracter*/
for(int i = len - 1 ;i >= 0; i--){

    // Si el caracter es un numero 0-9
    if(hex[i] >= '0' && hex[i]<= '9'){
        decimal += (hex[i]-'0')*base;
    }

    //Si el caracter es una letra A-F
    else if(hex[i]>='A' && hex[i] <= 'F'){
        decimal += (hex[i]-'A'+10)*base;
    }

    else if(hex[i]>='a' && hex[i] <= 'f'){
        decimal += (hex[i]-'a'+10)*base;
    }

    return decimal;
 } 



}

void decimal_a_hexadecimal(int num){
    printf("El num en hexadecimal es : %X \n",num);
}