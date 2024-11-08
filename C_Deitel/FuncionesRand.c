#include <stdio.h>
#include <stdlib.h>

int main(){

    int i; //contador 

    for(i=1;i<=20;i++){
        /*Obtiene y despliega un numero aleatorio entre 1 y 6*/
        printf("%10d",1+(rand()%6));

        /*si el contador es divisible entre 5 se empieza una nueva linea*/
        if(i%5==0){
            printf("\n");
        }

    }

    return 0;
}