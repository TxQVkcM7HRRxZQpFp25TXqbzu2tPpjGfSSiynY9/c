#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Funkcja do konwertowania słów na liczby
int wordToNumber(char* word) {
    if (strcmp(word, "one") == 0) return 1;
    if (strcmp(word, "two") == 0) return 2;
    if (strcmp(word, "three") == 0) return 3;
    if (strcmp(word, "four") == 0) return 4;
    if (strcmp(word, "five") == 0) return 5;
    if (strcmp(word, "six") == 0) return 6;
    if (strcmp(word, "seven") == 0) return 7;
    if (strcmp(word, "eight") == 0) return 8;
    if (strcmp(word, "nine") == 0) return 9;
    return 0;
}

// Funkcja do sumowania wartości energii
int sumOfEnergies(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open the file %s\n", filename);
        return -1;
    }

    char word[100];
    int sum = 0;

    while (fscanf(file, "%s", word) != EOF) {
        int length = strlen(word);
        // Sprawdź czy słowo jest liczbą
        if (isdigit(word[0])) {
            int first = word[0] - '0';
            int last = word[length - 1] - '0';
            sum += (first + last) * 10;
        }
        else {
            // Sprawdź czy słowo jest liczbą zapisaną słownie
            int number = wordToNumber(word);
            if (number > 0) {
                sum += number;
            }
        }
    }

    fclose(file);
    return sum;
}

int main() {
    char filename[] = "input.txt";
    int result = sumOfEnergies(filename);
    if (result != -1) {
        printf("Sum of energies: %d\n", result);
    }
    return 0;
}
