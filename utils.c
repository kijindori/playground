#include "utils.h"

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