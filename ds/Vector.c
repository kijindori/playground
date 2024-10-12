#include "Vector.h"

void initVector(Vector* v)
{
    v->capacity = 0;
    v->size = 0;
    v->data = (int*)malloc(0);
}

void reset(Vector* v, int i, int j, int val)
{
    assert(i <= v->capacity );
    assert(j <= v->capacity );

    /* 0으로 초기화 */
    for(int k = i; k < j; k++)
        v->data[k] = val;
}

void reserve(Vector* v, int n)
{
    if( n <= v->capacity)
        return;

    /* COPY */
    int* t = (int *)malloc(n * sizeof(int));
    for(int i =0; i<v->size; i++)
        t[i] = v->data[i];
    
    free( v->data );
    v->data = t;
    v->capacity = n;

    reset(v, v->size, v->capacity, 0);
}

void resize(Vector* v, int n, int val)
{
    reserve(v, n);

    if(v->size < n)
        reset(v, v->size, n, val);
    else
        reset(v, n, v->size, val);

    v->size = n;
}

int isFull(Vector* v)
{
    if(v->size < v->capacity)
        return 0;
    
    return 1;
}

int isEmpty(Vector* v)
{
    if(v->size > 0)
        return 0;
    
    return 1;
}


void pushBack(Vector* v, int item)
{
    assert( !isFull(v) );

    v->data[v->size++] = item;
}


int peekItem(Vector* v, int n)
{
    assert( n < v->size );
    return v->data[n];
}


/*
    TEST VECTOR
*/
int main()
{
    Vector v;
    initVector(&v);

    resize(&v, 5, 1);
    printf("%d\n", peekItem(&v, 1));
    printf("%d\n", peekItem(&v, 2));

    reserve(&v, 10);
    pushBack(&v, 3);
    printf("%d\n", peekItem(&v, 5));
    /*
        Assertion failed: n < v->size
        printf("%d\n", peekItem(&v, 7));
    */
}