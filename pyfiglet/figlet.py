from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

fonts = figlet.getFonts()

if len(sys.argv) == 3 and sys.argv[1] in ["-f","--font"] and sys.argv[2] in fonts:
    figlet.setFont(font=sys.argv[2])
elif len(sys.argv) == 1:
    figlet.setFont(font=random.choice(fonts))
else:
    print("Invalid usage")
    sys.exit(1)

s = input("Input: ")
print(figlet.renderText(s))
