#include <stdio.h>

#define LENGTH  3

char *words[LENGTH]; //Esto es un arreglo de punteros tipo char

int main(){

    void *gp; //This is for a generic pointers

    //char *pc;   //a pointer to a character
    //char **ppc; //a pointer to a character

    printf("generic pointer example \n");

    for(int i=0;i<LENGTH;i++){
        printf("%s \n",words[i]);
    }


    //initialize our string array
    words[0] = "zero";
    words[1] = "one";
    words[2] = "two";

    // a pointer to an array of strings , the same as a pointer to a pointer to a character
    printf("\n Now print the chars in each string ... \n");
    ppc = words; // initialize the pointer to a pointer to a character

    for(int i = 0 ;i<LENGTH;i++){

        ppc = words + i;
        pc = *ppc;

        while(*pc != 0){
            printf("%c",*pc);
            pc += 1;
        }
        printf("\n");
    }

    return 0;
}