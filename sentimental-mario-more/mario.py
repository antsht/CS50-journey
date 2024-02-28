height = 0
while not (height > 0 and height <= 8):
    try:
        height = int(input("Height: "))
    except ValueError:
        pass

for row in range(height):
    print(" " * (height - row - 1) + "#" * (row + 1) + "  " + "#" * (row + 1))
