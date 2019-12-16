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
        lc.push_front(a%10+'0');
        a/=10;
    }
}
int complit(list<char> &lc)
{
    for(auto i=lc.begin();i!=lc.end();i++)//&
    {
        if(*i=='&')
        {
            lc.erase(i);
            i=lc.begin();
        }
    }
    return 0;
}
void addcom(list<char> &lc,int num,int now)
{
    if (now<num-1)
    {
        auto lc1(lc);
        auto 
        i=lc1.begin();
        for(int o=0;o<2*now+1;o++)i++;
        lc1.insert(i,'+');
        auto lc2(lc);
        i=lc2.begin();
        for(int o=0;o<2*now+1;o++)i++;
        lc2.insert(i,'-');
        auto lc3=lc;
        i=lc3.begin();
        for(int o=0;o<2*now+1;o++)i++;
        lc3.insert(i,'*');
        auto lc4=lc;
        i=lc4.begin();
        for(int o=0;o<2*now+1;o++)i++;
        lc4.insert(i,'/');
        auto lc5=lc;
        i=lc5.begin();
        for(int o=0;o<2*now+1;o++)i++;
        lc5.insert(i,'&');
        addcom(lc1,num,now+1);
        addcom(lc2,num,now+1);
        addcom(lc3,num,now+1);
        addcom(lc4,num,now+1);
        addcom(lc5,num,now+1);
    }
    else
    {
        int x=0;
        for (auto i=lc.rbegin();i!=lc.rend();i++)
        {
            if (*i>='0'&&*i<='9')
            {
                x+=x*10+(*i-'0');
            }
        }
        if (x==complit(lc))
            cout<<x<<endl;
    }
    
}
int main(){
    int n=1998;
    //for (int n=100;n<1000;n++)
    {
        list<char> lc;
        getnumlist(n,lc);
        addcom(lc,lc.size(),0);
    }
    
}