from cs50 import get_string


def count_letters(text):
    sum = 0
    for l in text:
        if l.isalpha():
            sum += 1
    return sum


def count_words(text):
    sum = 1
    for l in text:
        if l.isspace():
            sum += 1
    return sum


def count_sentences(text):
    sum = 0
    for l in range(1, len(text)):
        if (text[l] in [".", "?", "!"]) and not (text[l - 1] in [".", "?", "!"]):
            sum += 1
    return sum


def main():
    text = get_string("Text: ")
    l = count_letters(text)
    print(l)
    w = count_words(text)
    print(w)
    s = count_sentences(text)
    print(s)
    index = 0.0588 * (l * 100.0 / w) - 0.296 * (s * 100.0 / w) - 15.8
    if index < 1:
        print("Before Grade 1")
    if index >= 16:
        print("Grade 16+")
    if index >= 1 and index < 16:
        print(f"Grade { round(index)}")


main()
