#include <stdio.h>
#include <stdbool.h>


int ArrayExperiments[3]={0,1,2};
int temp[3],a[3],b[3];
bool flagAcomodos = false;

void ChangeValue(int *PtrValue);


int main(void){
 
  int counter = 0 ;
  int centinela = 0;
 

  printf("Esto es un test para revisar mi conocimiento en C \n");
  
  /*Condicional por contador*/
  while(counter <= 10){
    counter++;
  }

  /*Valor centinela*/
  printf("Ingresa un valor para el valor centinela %d \n");
  scanf("%d",&centinela);

  do
  {
    //Aqui empieza a hacer los acomodos 
    for(int i=0;i<=3;i++){
        temp[i] = a[i];
        a[i] = b[i];
        b[i]=temp[i];
        flagAcomodos = true;
    }
  } while (centinela != 3);

  if(flagAcomodos){
     printf("Los acomodos fueron exitosos \n");
   }
  
  ChangeValue(ArrayExperiments);
  /*Usar un switch case para llamar a las funciones de paso de referencia y usar la funcion rand()*/
  return 0;
}

/*
Recordatorio de como funcionan los punteros 
int a = 2; 
int *PtrA; , PtrA es la direccion de una variable
PtrA = &a ; , PtrA toma la direccion de a usando el operador & de direccion

 */
/*Investigar*/
void ChangeValue(int *PtrValue){

   int valueToInsert = 24;
   //Iterar todos los valores 
   for(int i=0;i<=3;i++){
    //
    if(i==2){
        //ArrayExperiments[i] = valueToInsert; 
        *PtrValue =valueToInsert; 
    }
   }
}


