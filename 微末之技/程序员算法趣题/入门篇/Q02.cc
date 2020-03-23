/*
计算1000~9999之间的数
数位之间加入运算符计算得到等于其倒数的数
些数位之间可以没有运算符,但最少要插入 1 个运算符
例如:
    351:3*51=153
*/
//使用递归
#include <iostream>
int resave(int x,int length)
{
    int y=0;
    for(int i=0;i<length;i++)
    {
        y=y*10+x%10;
        x/=10;
    }
    return y;
}
void complet(int now,int *list,int step,int listlength,int x,int ad)
{
    if(step!=0)
    {
        //  +
        complet(step==listlength?list[0]:now+list[listlength-step],list,step-1,listlength,x,ad+1);
        //  -
        complet(step==listlength?list[0]:now-list[listlength-step],list,step-1,listlength,x,ad+1);
        //  *
        complet(step==listlength?list[0]:now*list[listlength-step],list,step-1,listlength,x,ad+1);
        //  /
        complet(step==listlength?list[0]:(now==0?1:now)/((list[listlength-step]==0)?1:list[listlength-step]),list,step-1,listlength,x,ad+1);
        //  &
        if (ad<(listlength-2))
        complet(step==listlength?list[0]:now*10+list[listlength-step],list,step-1,listlength,x,ad+1);
    }
    else
    {
        if (now==resave(x,listlength))
            printf("x:%d  = %d\n",now ,x);
    }
}
int length(int x)
{
    int count=0;
    while(x)
    {
        count++;
        x/=10;
    }
    return count;
}
int * split(int x)
{
    int l=length(x);
    int *a=(int *)malloc(sizeof(int)*l);
    for(int i=0;i<l;i++)
    {
        a[i]=x%10;
        x/=10;
    }
    return a;
}
int main()
{
    for(int i=1000;i<10000;i++)
    {
        int * a=split(i);
        complet(0,a,length(i),length(i),i,0);
        free(a);
    }
}