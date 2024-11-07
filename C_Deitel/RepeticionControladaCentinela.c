#include <stdio.h>

int main(){

    int contador;
    int calificacion;
    int total;

    float promedio;

    /*Fase de inicializacion*/
    total = 0 ;
    contador = 0 ;

    printf("Introduzca una cal , -1 para terminar \n");
    scanf("%d",&calificacion);

    /*Repetir el ciclo mientras no se introduzca un valor guardian*/
    while(calificacion != -1){
        total = total + calificacion;
        contador = contador + 1;
        /*Obtener la siguiente calificacion de un usuario */
        printf("Introduzca una cal , -1 para terminar");
        scanf("%d",&calificacion);
    }

    /*si el usuario introdujo almenos una calificacion*/
    if(contador != 0){
        /*Calcula el promedio de todas las calificaciones introducidas*/
        promedio = (float)total/contador;
        /*Despliega el promedio con dos digitos de precision*/
        printf( "El promedio del grupo es: %.2f\n", promedio );  
    }
    else{
        printf( "No se introdujeron calificaciones \n" );
    }


    return 0;
}
