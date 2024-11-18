#include <stdio.h>

#define TAM 10

void algunaFuncion(const int b[],int iniciaIndice, int tam);

int main(){

    int a[TAM] = {8,3,1,2,6,0,9,7,4,5};
    printf("La respuesta es : \n");
    algunaFuncion(a,0,TAM);
    printf("\n");

    return 0;
}

void algunaFuncion(const int b[],int iniciaIndice, int tam){

    if(iniciaIndice < tam){
       algunaFuncion(b,iniciaIndice+1,tam);
       printf("%d",b[iniciaIndice]);
    }
    
}