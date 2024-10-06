#include <stdio.h>

//Prototypes functions 
void SetAbit(int *byte,int position){
    *byte |=(1<<position);
}

void ClearAbit(int *byte,int position){
    *byte &=~(1<<position);
}

void ToggleBit(int *byte,int position){
    *byte ^=(1<<position);
}

void WriteAByte(int *address , int value){
    *address = value;
}