#include "queue.h"

void initQueue(Queue* q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue* q)
{
    return q->front == -1;
}

int isFull(Queue* q)
{
    
    return (q->rear + 1) % MAX_COUNT == q->front;
}

void enqueue(Queue* q, int d)
{
    if(isFull(q))
    {   
        printf("Queue is Full!\n");
        return;
    }

    if(isEmpty(q))
    {
        q->front = 0;
    }
    q->data[++q->rear] = d;
        
}

int dequeue(Queue* q)
{
    if(isEmpty(q))
    {
        printf("Queue is Empty!\n");
        return -1;   
    }

    int ret = q->data[q->front];

    if(q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }

    q->front = (q->front + 1) % MAX_COUNT;

    return ret;
}

/* TEST QUEUE */
int main()
{
    
    Queue q;
    initQueue(&q);
    //isEmpty
    dequeue(&q);

    //enqueue
    enqueue(&q, 1);
    enqueue(&q, 3);
    enqueue(&q, 5);
    enqueue(&q, 7);
    enqueue(&q, 9);

    //isFull
    enqueue(&q, 9);

    //dequeue
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));

    return 1;
}