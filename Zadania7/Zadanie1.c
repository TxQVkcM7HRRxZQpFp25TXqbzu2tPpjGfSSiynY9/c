#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert number words to digits
int word_to_digit(const char* word) {
    if (strcmp(word, "one") == 0) return 1;
    else if (strcmp(word, "two") == 0) return 2;
    else if (strcmp(word, "three") == 0) return 3;
    else if (strcmp(word, "four") == 0) return 4;
    else if (strcmp(word, "five") == 0) return 5;
    else if (strcmp(word, "six") == 0) return 6;
    else if (strcmp(word, "seven") == 0) return 7;
    else if (strcmp(word, "eight") == 0) return 8;
    else if (strcmp(word, "nine") == 0) return 9;
    return -1;  // Not a number word
}

// Function to find the first and last digit in a string
int process_line(char* line) {
    int first = -1, last = -1, digit;
    char* token;
    const char* delimiters = " ,;.!?-\n";

    token = strtok(line, delimiters);
    while (token != NULL) {
        if (sscanf(token, "%d", &digit) == 1) {  // Check if it's a direct digit
            if (first == -1) first = digit % 10;
            last = digit % 10;
        }
        else {
            digit = word_to_digit(token);  // Convert word to digit if applicable
            if (digit != -1) {
                if (first == -1) first = digit;
                last = digit;
            }
        }
        token = strtok(NULL, delimiters);
    }

    if (first != -1 && last != -1) {
        return first * 10 + last;
    }
    return 0;
}

int main() {
    FILE* file;
    char line[1024];
    int sum = 0;

    file = fopen("input.txt", "r");
    if (!file) {
        printf("File could not be opened.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        sum += process_line(line);
    }

    fclose(file);

    printf("Total sum of energy values is: %d\n", sum);
    return 0;
}
