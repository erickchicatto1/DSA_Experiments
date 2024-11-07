#include <stdio.h>

int main(){

    int num;
    printf("Introduce números positivos (introduce -1 para terminar):\n");

    do{
        scanf("%d",&num);
        if(num != -1){
           printf("Número introducido: %d\n", num);  
        }
    }while(num != -1);

    printf("Programa terminado \n");

    return 0;
}