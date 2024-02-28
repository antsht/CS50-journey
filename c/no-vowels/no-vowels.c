// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string replace(string str);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Wrong argument!");
        return 1;
    }
    string pseudo = replace(argv[1]);
    printf("%s\n", pseudo);
    free(pseudo);
}

string replace(string str)
{
    char *buf;
    buf = (char *) malloc(strlen(str) + 1);
    for (int i = 0, n = strlen(str); i <= n; ++i)
    {
        buf[i] = str[i] == 'a' ? '6' : str[i] == 'e' ? '3' : str[i] == 'i' ? '1' : str[i] == 'o' ? '0' : str[i];
    }
    return buf;
}