#include <stdio.h>

int main()
{
    const char string[5] = "101";

    int n = 0;
    int base = 2;
    int i = 0;
    while( string[i] != '\0')
    {
        n = n * base + ( string[i] - '0' );
        i++;
    }
        

    printf("%s 를 %d 진수 변환 : %d \n", string, base, n);

    return 0;
}