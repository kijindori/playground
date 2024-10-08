#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 10000
/*
    C 표준 라이브러리의 rand() 를 활용하여, 랜덤한 숫자를 출력합니다.
 */
int main()
{
    srand(time(NULL));
    for(int i=0;i<MAX_LENGTH;i++)
    {
        int random_num = rand() % 1000;
        char out;
        while (random_num > 0)
        {
            int div = random_num / 10;
            int mod = random_num % 10;
            random_num = div;
            out = '0' + mod; 
            putchar(out);
        }
        putchar('\n');
    }
    return 0;
}