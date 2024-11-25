#include <stdio.h>

void cambiarValor(int numero) {
    numero = 42; // Cambiamos el valor, pero solo en la copia local
    printf("Dentro de la función: %d\n", numero);
}

void cambiarValor2(int *numero) {
    *numero = 42; // Cambiamos el valor de la variable original usando el puntero
    printf("Dentro de la función: %d\n", *numero);
}


int main() {
    
    int x = 10;
    printf("Antes de la función: %d\n", x);
    cambiarValor(x);
    printf("Después de la función: %d\n", x); // x no cambia 

    printf("Antes de la función2: %d\n", x);
    cambiarValor2(&x); // Pasamos la dirección de x
    printf("Después de la función2: %d\n", x); // x sí cambia


    return 0;
}