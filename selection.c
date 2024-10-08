#include "selection.h"
#include <ctype.h>
#define MAX_ITEMS 10000
#define LINE_LIMIT 1000

void SelectionSort(int arr[], int n)
{
    for( int i = 0; i < n; i++ ) 
    {
        int min = i;
        for(int j =i; j<n;j++)
        {
            if( arr[min] > arr[j] )
            {
                min = j;
            }

            int t = arr[min];
            arr[min] = arr[j];
            arr[j] = t;
        }
        
    }
}

int readline(char str[])
{
    
    int c, i;

    for(i=0; i<LINE_LIMIT-1 && (c = getchar()) != EOF && c != '\n' ; i++ )
    
        str[i] = c;

    if( c == '\n')
        str[i++] = c;

    str[i] = '\0';
    return i;
}

int todigit(char str[], int base)
{
    int c, i;
    int num = 0;

    for(i=0; str[i] != '\n' && str[i] != '\0';i++)
    {
        num = num*base + str[i] - '0';
    }

    return num;
}

/* Test Selection Sort */
int main()
{   
    char line[LINE_LIMIT];
    int i = 0;
    int num = 0;
    
    int arr[MAX_ITEMS];


    while( readline(line) > 0 )
    {   
        arr[i++] = todigit(line, 10);
    }

    for(int j =0; j<i; j++)
        printf("%d\n", arr[j]);

    printf("TOTAL %d items \n", i);
    
    return 0;
}