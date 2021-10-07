#include "MyList.h"

int fibonacci(int number)
{
    if (number == 0)
        return 0;
    if (number == 1)
        return 1;
    return fibonacci(number-1) + fibonacci(number-2);
}

double Fact(int x) 
{ 
    if (x==0)
    return 1;
    return x*Fact(x-1);
}
