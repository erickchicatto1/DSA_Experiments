#include <stdio.h>

int main(){

    int A[3][3],i,j;
    printf("Size of integer variable : %d Bytes",sizeof(int));

    printf("\n Enter the array element \n");

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
         scanf("%d",&A[i][j]);
        }
    }

    printf("\n Row   Col    - Address   -Values  ");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){

            printf("\n  %d  %d   %u     %d   ",i,j,&A[i][j]);

        }
    }

 
}