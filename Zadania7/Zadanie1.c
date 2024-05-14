#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

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

int find_first_digit(const char* line) {
    const char* words[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (int i = 0; i < strlen(line); ++i) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
        for (int j = 0; j < 9; ++j) {
            int len = strlen(words[j]);
            if (strncmp(line + i, words[j], len) == 0) {
                return word_to_digit(words[j]);
            }
        }
    }
    return -1;
}

int find_last_digit(const char* line) {
    const char* words[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (int i = strlen(line) - 1; i >= 0; --i) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
        for (int j = 0; j < 9; ++j) {
            int len = strlen(words[j]);
            if (i - len + 1 >= 0 && strncmp(line + i - len + 1, words[j], len) == 0) {
                return word_to_digit(words[j]);
            }
        }
    }
    return -1;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int total_sum = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        int first_digit = find_first_digit(line);
        int last_digit = find_last_digit(line);

        if (first_digit != -1 && last_digit != -1) {
            int energy_value = first_digit * 10 + last_digit;
            total_sum += energy_value;
        }
    }

    fclose(file);
    printf("Total sum of energy values: %d\n", total_sum);
    return 0;
}
