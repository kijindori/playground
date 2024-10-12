#include <stdio.h>
#define MAX_COUNT 5
typedef struct Queue
{
    int front;
    int rear;
    int data[MAX_COUNT];
}Queue;


void initQueue(Queue* q); 
int isEmpty(Queue* q);
int isFull(Queue* q);
void enqueue(Queue* q, int d);
int dequeue(Queue* q);



