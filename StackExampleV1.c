#include <stdio.h>
#include <stdlib.h>


#define MAX 100

typedef struct {
  int items[MAX];
  int top;
}Stack;




//Init the stack
void initialize(Stack *stack){
    stack->top =  -1;
}

//Comprueba si el stack esta lleno 
int isFull(Stack *stack){
    return stack->top == MAX-1;
}

//Comprueba si el stack esta vacio
int isEmpty(Stack *stack){
    return stack->top  == -1;
}

//Comprueba si el stack esta vacio
void push(Stack *stack, int item){

    if(isFull(stack)){
        printf("Stack overflow \n");
        return;
    }

    stack->items[++(stack->top)] = item; // Debuggear esta linea de codigo 
    printf("%d pushed to stack \n");
}

//Elimina y devuelve el elemento superior del stack
int pop(Stack *stack){
    if(isEmpty(stack)){
        printf("Stack underflow \n");
        return -1;
    }

  return stack->items[(stack->top)--]; // debug
}


//Devuelve el elemento superior del stack sin eliminarlo
int peek(Stack *stack){

    if(isEmpty(stack)){
        printf("Stack is empty \n ");
        return -1;
    }

    return stack->items[stack->top];//debug
}


int main() {
    Stack stack;
    initialize(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("%d popped from stack\n", pop(&stack));
    printf("Top element is %d\n", peek(&stack));

    return 0;
}
