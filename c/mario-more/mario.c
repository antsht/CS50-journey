#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    while ((8 < height) || (height < 1))
    {
        height = get_int("Height: ");
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (j < height - i - 1)
                printf(" ");
            else
                printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; ++j)
        {
            printf("#");
        }
        printf("\n");
    }
}