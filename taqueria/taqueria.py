
menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}
try:
    while True:
        sum = 0
        while True:
            item = input("Item: ").title()
            if item in menu:
                sum += menu[item]
except EOFError:
    print()
print(f"Total: ${sum}")
