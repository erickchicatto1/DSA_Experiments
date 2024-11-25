#include <stdio.h>


int main(){

    int a;  /*a es un entero*/
    int *ptrA; /*es un apuntador a un entero , direccion*/

    a = 7; 
    ptrA = &a; // Toma la direccion de a y su valor tambien 

    /*Muestra de valores */
    printf("la direccion de a es %p \n El valor de ptrA es %p \n",&a,ptrA);

    printf("\n El valor de a es %d \n El valor de *ptrA es %d \n",a,*ptrA);

    return 0;
}