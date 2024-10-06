#include <stdio.h>

int main(){

    int *p;
    int a[]={100,200,300,400};
    p=a; // to link with the array values 

    for(int i=0;i<4;i++){
        printf("Value = %d ,Address = %p\n",*p,p );
        p = p + 1;
    }



    return 0;
}