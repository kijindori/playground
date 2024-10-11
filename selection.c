#include "utils.h"
#include <ctype.h>
#include <time.h>

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
        }

        int t = arr[min];
        arr[min] = arr[i];
        arr[i] = t;
    }
}


/* Test Selection Sort */
int main()
{   
    printf("SEELCTION SORT TESTING>>> \n");
    
    char line[LINE_LIMIT];
    int i = 0;
    int j = 0;
    
    int arr[MAX_ITEMS];

    

    while( readline(line) > 0 )
    {   
        arr[i++] = todigit(line, 10);
    }

    
    time_t t0 = time(NULL);
    SelectionSort(arr, i);

    printf("TOTAL %d items \n", i);
    printf("%d seconds... \n", time(NULL) - t0);

    return 0;
}