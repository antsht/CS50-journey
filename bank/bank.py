str = input("Greeting: ")

if str[0:5].lower() == "hello":
    print("$0")
elif str[0].lower() == "h":
    print("$20")
else:
    print("$100")
