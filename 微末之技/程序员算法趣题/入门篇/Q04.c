/*
    切分木棒
*/
#include <stdio.h>
#include <stdlib.h>
struct math{
    int nowp;
    int max;
    int *vec;
}math;
int main()
{
    struct  math vnum;
    vnum.nowp=0;
    vnum.max=100;
    vnum.vec=(int *)malloc(vnum.max*sizeof(int));
    //初始化

    int sum=0;//计次

    int n,m;
    scanf("%d %d",&n,&m);
    vnum.vec[vnum.nowp++]=n;
    int works=1;//是否工作
    while (1)
    {
        if(works)
        {
            works=0;
            sum++;
            //检测数组大小是否足够
            if (vnum.max-10<vnum.nowp+m)
            {
                vnum.max+=100+vnum.nowp+m;
                vnum.vec=(int *)realloc(vnum.vec,vnum.max*sizeof(int));
                if (vnum.vec==NULL)
                {
                    puts("无法分配内存!（内存不足）");
                    return 0xE;//ERROR
                }
            }
            //足够的话我们
            int tmp=vnum.nowp;//存储现在有多少个木棍
            int tmp1=m;//本回合可使用的人手
            for(int i=0;i<tmp;i++)
            {
                if((vnum.vec[i]!=1)&&(tmp1>0))
                {
                    tmp1--;
                    works=1;
                    int tmp2=vnum.vec[i];
                    vnum.vec[i]/=2;
                    vnum.vec[vnum.nowp++]=tmp2-vnum.vec[i];
                }
            }
            /*//调试输出
            for(int i=0;i<vnum.nowp;i++)
            {
                printf("%d ",*(vnum.vec+i));
            }
            putchar('\n');*/
        }
        else
        {
            printf("%d\n",sum-1);
            return 0;
        }
    }
    return -1;
}