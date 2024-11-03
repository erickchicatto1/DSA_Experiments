#include<stdio.h>

//funcion para imprimir un saludo
void hello_fromC(){
    printf("Hello from C \n");
}

int add(int a, int b){
    return a + b;
}

int substract(int a , int b){
    return a - b;
}

int multiply(int a, int b){
    return a*b;
}

float divide(int a, int b){

    if(b==0){
        printf("Error div by zero \n");
        return 0;
    }

    return (float)a/b;
}

int is_event(int n){
    return n%2==0;  // Retorna 1 (true) si es par, 0 (false) si es impar
}