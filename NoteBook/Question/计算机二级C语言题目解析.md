# 1.程序运行的结果是
```c
#include <stdio.h>
int main()
{
    char *mm[4]={"abcd","1234","mnop","5678"};
    char **pm=mm;
    int i;
    for (i=0;i<4;i++)
        printf("%s",pm[i]+i);
    printf("\n");
    return 0;
}
```
解析
```
重点 pm[i]+i，i在1~4之间
pm指向 字符串的指针
pm+0 指向 "abcd"
pm+1 指向 "1234"
那么pm[i]取得了指向了-字符-的指针
pm[0]指向了'a'
pm[0]+1 指向了'b'
那么pm[i]+i 指向的分别是 'a' '2' 'o' '8'
由于printf("%s")输出字符串时由开始的指针的字符一直输出直到'\0'即char a=0;
所以循环输出了"abcd234op8"
```
# 2.设有以下说明和语句:int x[3][4],(\*p)[4];p=a;则与表达式*(*p+2)等价的选项是
```c
int x[3][4],(*p)[4];
p=a;
```
```
int x[3][4];
建立了一个3行4列的数组
*(p+x)
由x指定了第几行的数据
这里(*p+2) 它没有指定第几行就是第0行的数据
而 +2 就是 第2列的数据
那么找到同样是描述第0行第2列的代码；
如*(*x+2),x[0][2],(*x)[2],*x[0]+2
```
# 3.如有以下程序 输入3时 结果为:
```c
#include <stdio.h>
int main()
{
    int i,data;
    scanf("%d",&data);
    for(i=0;i<5;i++)
    {
        if (i<data)
            continue;
        printf("%d,",i);
    }
    putchar('\n');
}
```
```
2个重点 循环i<5; i<data
是小于
也就是说 循环不会到5 因为是小于5 不是小于等于5
i<data 也就是说只要大于等于data就会输出这个数
循环 中 只有 0,1,2,3,4
输入 3
3大于等于data 输出 3, 并继续循环
所以输出 3,4,
```
# 4 有如下程序，则输出为
```c
#include <stdio.h>
int main()
{
    int a=0x13;
    printf("%d\n",a+1);
}
```
```
这道题目考得非常简单
就是一个16进制转10进制
0x13= 16+3 = 19
a= 19
输出 a+1 即 20
```
# 5.为了建立如图所示的存储结构，链表，在[]处因填入的选项是
```c
struct link{char data;[]}node;
```
```
这个必然就是
struct link *next;
除非是c++ 不然不可以使用 link *next;
```
# 6.有以下程序 ，结果为什么
```c
#include <stdio.h>
#define N 4
int fun(int a[][N])
{
    int i,j,x=0;
    for(i=0;i<N;i++)
    for(j=0;j<N;j++)
    if (i==j)
        x+=a[N-1-j][i];
    return x;
}
int main()
{
    int x[N][N]={{1 ,2 ,3 ,4 },
                 {5 ,6 ,7 ,8 },
                 {9 ,10,11,12},
                 {13,14,15,16}}
    ,y;
    y=fun(x);
    printf("%d\n",y);
    return 0;
}
```
```
if (i==j)
说明了 x 只加4次
分别在i和j在 0,1,2,3 时
我们替换 i j 在 a[N-1-j][i]
分别是a[4-1-0][0]=
a[3][0]=13
a[2][1]=10
a[1][2]=7
a[0][3]=4
那么和为34
```
# 7. 有以下程序
```c
#include <stdio.h>
int main()
{
    int i=1;
    i=i^i;
    printf("%d\n",i);
    return 0;
}
```
```
^ 这个是异或运算 位运算 不是 几次方
计算二进制表示下 2个 数 每位一一对应 如果相同就变成0 如果不同就变成1
所以 i与i完全相同 所有位都变成0
所以答案是0
```
