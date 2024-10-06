#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int dato;
    struct nodo *siguiente; //que significa esto?
};


int main(){

    struct nodo *cabeza=NULL;
    struct nodo *nuevoNodo;

    //Para crear 3 nodos
    for(int i=0;i<3;i++){
      
      nuevoNodo = (struct nodo*)malloc(sizeof(struct nodo));
      nuevoNodo->dato = i+1;
      nuevoNodo->siguiente = cabeza;
      cabeza= nuevoNodo;
    }

    //Imprimir la lista
    struct nodo *actual = cabeza;
    while(actual != NULL){
         printf("%d ", actual->dato);
         actual = actual->siguiente;
    }
    
    printf("\n");
    return 0;
}


