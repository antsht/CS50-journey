#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    // printf("%s\n", text);
    int l, w, s;
    l = count_letters(text);
    w = count_words(text);
    s = count_sentences(text);
    // printf("%d letters\n%d words\n%d sentences\n", l, w, s);
    double index = 0.0588 * (l * 100.0 / w) - 0.296 * (s * 100.0 / w) - 15.8;
    // printf("Raw index %lf\n", index);
    if (index < 1)
        printf("Before Grade 1\n");
    if (index >= 16)
        printf("Grade 16+\n");
    if (index >= 1 && index < 16)
        printf("Grade %d\n", (int) (index * 10) % 10 < 5 ? (int) index : (int) index + 1);
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; ++i)
        if (isalpha(text[i]))
            sum++;
    return sum;
}
int count_words(string text)
{
    int sum = 1;
    for (int i = 0, n = strlen(text); i < n; ++i)
        if (text[i] == ' ')
            sum++;
    return sum;
}
int count_sentences(string text)
{
    int sum = 0;
    for (int i = 1, n = strlen(text); i < n; ++i)
        if ((text[i] == '.' || text[i] == '?' || text[i] == '!') &&
            !(text[i - 1] == '.' || text[i - 1] == '?' || text[i - 1] == '!'))
            sum++;
    return sum;
}