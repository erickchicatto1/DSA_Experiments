#include <stdio.h>


int main(){

    int contador;
    int calificacion;
    int total;
    int promedio;

    /*Fase de inicializacion*/
    total = 0;
    contador = 1;

    while(contador <= 10){
        printf("Introduzca la calificacion \n");
        scanf("%d",&calificacion);
        total = total + calificacion;
        contador = contador + 1 ;
    }

    promedio = total / 10;
    printf("El promedio total es : %d \n" ,promedio);

    return 0;
}