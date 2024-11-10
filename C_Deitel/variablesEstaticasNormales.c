#include <stdio.h>

void ejemplo(){

    int contador_local = 0 ;
    static int contador_estatico = 0;

    contador_local++;
    printf("Contador local: %d\n", contador_local);

    contador_estatico++;
    printf("Contador estatico: %d\n", contador_estatico++); //el ++ es el que hace que se incrementen valores
}

int main(){

    for(int i=0;i<=10;i++){
        ejemplo();
    }
    
    return 0;
}