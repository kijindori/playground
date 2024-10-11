#include <stdio.h>

#define MAX_COUNT 5

typedef struct Stack
{
    int top;
    int arr[MAX_COUNT];
}Stack, stack;

void initStack(Stack* s);
int peek(Stack* s);
int pop(Stack* s);
void push(int x , Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);