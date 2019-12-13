/**
 求用十进制、二进制、八进制表示都是回文
**/
#include <iostream>
#include <vector>
using namespace std;
void itoa(int num,vector<char> &save,int base)
{
    while (num)
    {
        save.push_back(num%base);
        num/=base;
    }
}
/*
测试是否是回文
是返回1 否返回0
*/
bool huiwen(vector<char> &testvec)
{
    for( int i=0;i<testvec.size()/2;i++)
    {
        if(testvec[i]!=testvec[testvec.size()-1-i])
            return false;
    }
    return true;
}
int main()
{
    int n=11;
    int base[]={2,8,10};
    for (int n=1;n<10000;n++)
    {
        for (int i:base)
        {
            vector<char> vsave;
            itoa(n,vsave,i);
            if(!huiwen(vsave))
                break;
            if(huiwen(vsave)&& i==base[sizeof(base)/sizeof(base[0])-1])
                cout<<"符合条件:"<<n<<endl;
        }
    }
}