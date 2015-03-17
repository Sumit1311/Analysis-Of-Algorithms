#include "dividenconquer.h"
#include <iostream>
using namespace std;

int power(int x,int y)
{
    if(y==0)
    {
        return 1;
    }
    int temp=power(x,y/2);
    if(y%2 == 0)
    {
        return temp * temp;
    }
    else
    {
        if(y>0)
        {
            return temp * temp * x;
        }
        else
        {
            return (temp * temp)/x;
        }
    }

}
