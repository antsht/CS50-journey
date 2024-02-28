#include <stdio.h>



int main()
{
    long sum = 0;
    int divider = 5;
    while ((123456789 / divider) > 0)
    {
        sum += 123456789 / divider;
        divider *= 5;
    }

    printf("%ld", sum);
    return 0;
}

