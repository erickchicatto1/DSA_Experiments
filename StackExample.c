#include <stdio.h>
#include <stdlib.h>

int stack[100];
int size;
int top = 1 ; 

void push();
void display();
void pop();
void isEmpty();


int main(){

    int opt;
    printf("\n Enter size of the stack ");
    scanf("%d",&size);
    printf("1.Push  2.Pop  3. Top of the stack  4.isEmpty  5.Display  6.Exit");

    while(1){
        printf("\n Enter the option");
        scanf("%d",&opt);

        switch(opt){

            case 1: push();
                    break;
            case 2: pop();
                    break;
            case 4: isEmpty();
                    break;
            case 5: display();
                    break;

            case 6:  exit(1);

            default:
                   printf("\n Invalid option");


        }


    }

    return 0;
}


void push(){
    if(top==size-1){
        printf("\n Stack is overflow ");
    }
    else{
        top++;
        printf("\nEnter stack element");
        scanf("%d",stack[top]);
    }

}

void display(){
    int i;
    if(top==-1){
        printf("\n Stack is empty");
    }
    else{
        printf("\n Stack elements :");
        for(i=0;i<=top;i++){
            printf("%d",stack[i]);
        }
    }


}


void pop(){
    int temp;

    if(top==-1){
        printf("\n Stack is underflow");
    }

    else{
        temp = stack[top];
        top--;
        printf(" \n Deleted elements ");

    }


}

void isEmpty(){

    if(top==-1){
        printf("\n Stack is empty");
    }
    else{
        printf("\n Stack is not empty");
    }


}