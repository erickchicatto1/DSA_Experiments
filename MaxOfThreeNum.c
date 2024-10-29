#include <stdio.h>

int maximum(int x, int y, int z);
int arrayNum[100];

int main(void){

    int counter, num;
    
    //1. Save the value in the counter
    printf("Enter the counter \n");
    scanf("%d% %d %d",&counter);

    //2. Store the values in the array
    for(int i = 0 ; i<=counter ; i++){
       printf("Enter the num of array \n");
       scanf("%d ",&num);
       arrayNum[i]=num; 
    }

    //3. Pass the values to the max function 
    int maxValue = arrayNum[0];
    for(int i=0; i<counter-2 ; i++){
        int currentMax = maximum(arrayNum[i], arrayNum[i + 1], arrayNum[i + 2]);
        if(currentMax > maxValue){
            maxValue = currentMax;
        }
    }

    return 0;
}

//Is best idea that this use an array and then can compare
int maximum(int x, int y, int z){
    
    int max = x;

    if(y>max){
        max = y;
    }

    if(z>max){
        max = z;
    }
    return max;
}