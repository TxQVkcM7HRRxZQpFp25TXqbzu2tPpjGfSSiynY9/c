#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    return -1;
}

void convert_words_to_digits(char* line) {
    char* result = malloc(strlen(line) + 1);
    char* token, * original = line, * res_ptr = result;
    int digit;

    token = strtok(line, " ,.-");
    while (token != NULL) {
        digit = word_to_digit(token);
        if (digit != -1) {
            *res_ptr++ = '0' + digit;
        }
        else {
            while (*token) {
                *res_ptr++ = *token++;
            }
        }
        token = strtok(NULL, " ,.-");
    }
    *res_ptr = '\0';
    strcpy(original, result);
    free(result);
}

int main() {
    FILE* file = fopen("input.txt", "r");
    char line[256];
    int total = 0;

    if (file == NULL) {
        printf("Nie udało się otworzyć pliku.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        char* ptr = line;
        int first_digit = -1, last_digit = -1;

        convert_words_to_digits(line);

        while (*ptr) {
            if (*ptr >= '0' && *ptr <= '9') {
                if (first_digit == -1) first_digit = *ptr - '0';
                last_digit = *ptr - '0';
            }
            ptr++;
        }

        if (first_digit != -1 && last_digit != -1) {
            total += first_digit * 10 + last_digit;
        }
    }

    fclose(file);
    printf("Całkowita wartość energii: %d\n", total);

    return 0;
}
