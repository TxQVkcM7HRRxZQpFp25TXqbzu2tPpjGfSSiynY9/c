#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

int word_to_digit(const char* word) {
    if (strcmp(word, "one") == 0) return 1;
    if (strcmp(word, "two") == 0) return 2;
    if (strcmp(word, "three") == 0) return 3;
    if (strcmp(word, "four") == 0) return 4;
    if (strcmp(word, "five") == 0) return 5;
    if (strcmp(word, "six") == 0) return 6;
    if (strcmp(word, "seven") == 0) return 7;
    if (strcmp(word, "eight") == 0) return 8;
    if (strcmp(word, "nine") == 0) return 9;
    return -1;
}

void extract_digits(const char* line, int* first_digit, int* last_digit) {
    *first_digit = -1;
    *last_digit = -1;
    int len = strlen(line);
    char word[MAX_LINE_LENGTH];
    int word_index = 0;

    for (int i = 0; i < len; i++) {
        if (isdigit(line[i])) {
            int digit = line[i] - '0';
            if (*first_digit == -1) *first_digit = digit;
            *last_digit = digit;
        }
        else if (isalpha(line[i])) {
            word[word_index++] = line[i];
            word[word_index] = '\0';
            if (word_index >= 3) {
                int digit = word_to_digit(word);
                if (digit != -1) {
                    if (*first_digit == -1) *first_digit = digit;
                    *last_digit = digit;
                    word_index = 0;
                }
            }
        }
        else {
            word_index = 0;
        }
    }
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int total_sum = 0;

    while (fgets(line, sizeof(line), file)) {
        int first_digit, last_digit;
        extract_digits(line, &first_digit, &last_digit);
        if (first_digit != -1 && last_digit != -1) {
            int number = first_digit * 10 + last_digit;
            total_sum += number;
        }
    }

    fclose(file);

    printf("Total sum: %d\n", total_sum);

    return 0;
}
