#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


typedef struct Vector
{
    int size;
    int capacity;
    int* data;
} Vector, vector;


void initVector(Vector* v);
void reserve(Vector* v, int n);
void resize(Vector* v, int n, int val);
void pushBack(Vector* v, int val);
int peekItem(Vector* v, int n);
void reset(Vector* v, int i, int j, int val);

//TODO
/*
    erase,
    iterator,
    ETC.....
*/