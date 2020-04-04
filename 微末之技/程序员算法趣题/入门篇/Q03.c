#include <stdio.h>
#include <stdlib.h>
#define N 100
int main()
{
    int *list=(int *)malloc(sizeof(int)*N);
    for (int i=1;i<=100;i++)
    {
        for (int o=1;i*o<=100;o++)
        {
            list[i*o-1]=list[i*o-1]==1?0:1;
        }
    }
    for(int i=0;i<100;i++)
    {
        if (list[i])
            printf("%d  ",i+1);
    }
    return 0;
}