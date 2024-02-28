#include <cs50.h>
#include <stdio.h>

int isValid(long numToCheck);
string cardsys(long numToCheck);

int main(void)
{
    long cardNum = 0;
    while (cardNum == 0)
    {
        cardNum = get_long("Number: ");
    }
    if ((9999999999999999 < cardNum) || (cardNum < 1000000000000) || !isValid(cardNum))
        printf("INVALID\n");
    else
        printf("%s\n", cardsys(cardNum));
}

int isValid(long numToCheck)
{
    int tmpSum = 0;
    int odd = 1;
    while (numToCheck > 0)
    {
        tmpSum += odd * (numToCheck % 10) +  (odd ^ 0x1) * (((numToCheck % 10) * 2) / 10 + ((numToCheck % 10) * 2) % 10);
        numToCheck /= 10;
        odd = odd ^ 0x1;
    }
    if (tmpSum % 10 == 0)
        return 1;
    return 0;
};

string cardsys(long numToCheck)
{
    int d1, d2, len;
    d1 = 0;
    d2 = 0;
    len = 0;
    while (numToCheck > 0)
    {
        d2 = d1;
        d1 = numToCheck % 10;
        len++;
        numToCheck /= 10;
    }
    if (d1 == 4 && (len == 13 || len == 16))
        return "VISA";
    if (d1 == 3 && len == 15 && (d2 == 4 || d2 == 7))
        return "AMEX";
    if (d1 == 5 && len == 16 && (d2 >= 1 && d2 <= 5))
        return "MASTERCARD";
    return "INVALID";
};
