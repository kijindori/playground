#include <stdio.h>
#include "stack.h"


void initStack(Stack* s)
{
    s->top = -1;
}

int isEmpty(Stack* s)
{
    if(s->top == -1)
        printf("Stack is EMPTY! \n");

    return s->top == -1;
}

int isFull(Stack* s)
{
    if(s->top == MAX_COUNT-1)
        printf("Stack is FULL! \n");

    return s->top == MAX_COUNT-1;
}

int pop(Stack* s)
{
    if(isEmpty(s))
        return -1;
        
    int ret = peek(s);
    s->top--;

    return ret;
}

void push(int x, Stack* s)
{
    if(isFull(s))
        return;
    
    s->arr[++s->top] = x;
}

int peek(Stack* s)
{
    return s->arr[s->top];
}



/* TEST STACK */
int main()
{
    Stack s;
    /* Init */
    initStack(&s);

    /* Is Empty ? */
    pop(&s); // STACK IS EMPTY

    push(1,&s);
    push(3,&s);
    push(5,&s);
    push(7,&s);
    push(9,&s);

    /* Is Full ? */
    push(11,&s); // STACK IS FULL

    printf("POP: %d \n", pop(&s));
    printf("POP: %d \n", pop(&s));
    printf("POP: %d \n", pop(&s));
    printf("POP: %d \n", pop(&s));
    
    return 1;
}

