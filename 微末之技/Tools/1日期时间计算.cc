#include <iostream>
#include <string>
#include <cctype>
class time
{
private:
    /* data */
public:
    int year;
    int mouth;
    int day;
    int hour;
    int min;
    int sec;
    time(std::string times);
    void times(int hour,int min,int sec);
    void times(int hour,int min);
    ~time();
};

time::time(std::string times)
{
    int num=0;
    char up=0;
    for(char ci:times)
    {
        if(isdigit(ci))
        {
            num=num*10+ci-'0';
        }
        else if(isascii(ci))
        {
            switch (ci)
            {
            case 'y':
                this->year=num;
                num=0;
                up='y';
                break;
            case 'm':
                if(up='y')
                {
                    this->mouth=num;
                    
                }
                else
                {
                    this->min=num;
                }
                num=0;
                up='m';
                break;
            case 'd':
                this->day=num;
                num=0;
                up='d';
                break;
            case 'h':
                this->hour=num;
                num=0;
                up='h';
                break;
            case 's':
                this->day=num;
                num=0;
                up='s';
                break;
            default:
                break;
            }
        }
        
    }
}
void time::times(int hour,int min,int sec)
{
}
void time::times(int hour,int min)
{
}

time::~time()
{
}
