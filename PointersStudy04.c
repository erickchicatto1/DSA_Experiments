#include <stdio.h>


int main(int argc, char **argv){

    int i;

    //1.Iterate over an array of args 
    for(int i=0;i<argc ;i++){
        printf("arg %d is %s \n",i,argv[i]);
    }

    printf("\n\n");

    //2. For dereferencing the string 
    for(i=0;i<argc;i++){
        printf("arg %d is %s \n",i,*argv);
        argv +=1;
    }



    return 0;
}