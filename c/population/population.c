#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startsize = 0;
    while (startsize < 9)
    {
        printf("Start size: ");
        scanf("%d", &startsize);
        printf("\n");
    }
    int endsize = 0;
    while (endsize < startsize)
    {
        printf("End size: ");
        scanf("%d", &endsize);
        printf("\n");
    }
    int years = 0;
    int currentpopulation;
    currentpopulation = startsize;
    while (currentpopulation < endsize)
    {
        years++;
        currentpopulation = currentpopulation + currentpopulation / 3 - currentpopulation / 4;
    }
    printf("Years: %d\n", years);
    return 0;
}
