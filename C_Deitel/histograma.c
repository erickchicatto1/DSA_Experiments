#include <stdio.h>

#define TAM     10

int main(){

    /*Inicializamos el arreglo*/
    int n[TAM]={19,3,15,7,11,9,13,5,17,1};
    int i;  //Contador for externo para los elementos del arreglo 
    int j; //contador interno cuenta *s en cada barra del histograma

    printf( "%s%13s%17s\n", "Elemento", "Valor", "Histograma" );

    /*Para cada elemento del arreglo n , muestra una barra en el histograma */
    for(i=0;i<TAM;i++){
        printf( "%7d%13d        ", i, n[ i ]) ;

        for(j=1;j<=n[i];j++){ //n[i] se encarga de contar en el num del array 
            printf("%c",'*');
        }

      printf("\n");
    }

    return 0;
}