/*
计算1000~9999之间的数
数位之间加入运算符计算得到等于其倒数的数
些数位之间可以没有运算符,但最少要插入 1 个运算符
例如:
    351:3*51=153
*/
#include <iostream>
#include <list>
using namespace std;
void getnumlist(int a,list<char> &lc)
{
    while (a)
    {
        lc.push_front(a%10);
        a/=10;
    }
    
}
void addcom(list<char> lc,int n)
{
    if (n)
    {
        auto lc1=lc;
        
    }
    else
    {
        /* code */
    }
    
}
int main(){
    for (int n=100;n<1000;n++)
    {
        list<char> lc;
        getnumlist(n,lc);
        
    }
}