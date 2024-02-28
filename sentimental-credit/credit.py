from cs50 import get_int


def isValid(number):
    tmpSum = 0
    odd = 1
    while number > 0:
        tmpSum += odd * (number % 10) + (odd ^ 0x1) * (
            ((number % 10) * 2) // 10 + ((number % 10) * 2) % 10
        )
        number = number // 10
        odd = odd ^ 0x1
    if tmpSum % 10 == 0:
        return 1
    return 0


def cardSys(number):
    d1 = 0
    d2 = 0
    len = 0
    while number > 0:
        d2 = d1
        d1 = number % 10
        len += 1
        number = number // 10
    if d1 == 4 and (len == 13 or len == 16):
        return "VISA"
    if d1 == 3 and len == 15 and (d2 == 4 or d2 == 7):
        return "AMEX"
    if d1 == 5 and len == 16 and (d2 >= 1 and d2 <= 5):
        return "MASTERCARD"
    return "INVALID"


def main():
    number = get_int("Number: ")
    if (9999999999999999 < number) or (number < 1000000000000) or not isValid(number):
        print("INVALID")
    else:
        print(cardSys(number))


main()
