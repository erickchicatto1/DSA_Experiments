#include <stdio.h>

#define BUFFER_SIZE    5

typedef struct{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int size;
}CircularBuffer;

void initBuffer(CircularBuffer *cb){
    cb->head = 0 ;
    cb->tail = 0;
    cb->size = 0;
}


int isFull(CircularBuffer *cb){
    return cb->size == 0;
}

int isEmpty(CircularBuffer *cb,int item){
    if(!isFull(cb)){
        cb->buffer[cb->tail] = item; // analizar que es lo que hace ?
        cb->tail = (cb->tail + 1) % BUFFER_SIZE; //analizar que es lo que hace ?
        cb->size++;
    }
}


int dequeue(CircularBuffer *cb){
    int item = -1;
    
    if(){

    }


}

/** */