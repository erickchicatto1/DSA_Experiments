#include <stdio.h>

#define LENGTH  3   

int data[LENGTH];

int main(){

    int *pi;  //a simple pointer to an integer
    int **ppi; //a pointer to a pointer to an integer

    printf("Multiple indirection example \n");

    //Initialize out integer array
    for(int i=0;i<LENGTH;i++){
        data[i]=i;
    }
    for(int i=0;i<LENGTH;i++){
        printf("%d \n",data[i]);
    }

    // A simple pointer to a pointer to an integer
    pi = data ; // set the pointer to an integer to the start of the data array
    ppi = &pi;  // and set the pointer to a pointer to pi itself

    for(int i=0;i<LENGTH;i++){

        printf("\n Loop[%d] array address is %p \n",i,data);
        printf("item pointed to by pi is %d \n",*pi);
        printf("item pointed to by ppi is %p \n",**ppi);
        printf("item pointed to by double indirection of ppi is %d \n\n",**ppi);
        printf("The address of pi is %p and the value of pi (what it points to) is %p\n\n",&pi,ppi);

        pi += 1; //advance the pointer to point to the next element of the data array



    }



    return 0;
}