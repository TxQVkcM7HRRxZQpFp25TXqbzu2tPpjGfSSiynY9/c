#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512

typedef struct {
    int red;
    int green;
    int blue;
} DiceSet;

// Function to parse the dice counts from a given string and update the DiceSet structure
void parse_dice(const char *str, DiceSet *set) {
    set->red = 0;
    set->green = 0;
    set->blue = 0;
    char color[10];
    int count;
    const char *ptr = str;
    while (sscanf(ptr, "%d %9s", &count, color) == 2) {
        if (strstr(color, "red")) set->red += count;
        if (strstr(color, "green")) set->green += count;
        if (strstr(color, "blue")) set->blue += count;
        ptr = strstr(ptr, ";");
        if (ptr) ptr++;
        else break;
    }
}

// Function to check if a game is possible given the maximum number of dice available
int is_possible_game(const DiceSet *max_set, const DiceSet *game_sets, int num_sets) {
    for (int i = 0; i < num_sets; i++) {
        if (game_sets[i].red > max_set->red || game_sets[i].green > max_set->green || game_sets[i].blue > max_set->blue) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *file = fopen("input_2.txt", "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    DiceSet max_set = {12, 13, 14};
    int possible_sum = 0;
    long long power_sum = 0;

    // Read each line from the input file and process it
    while (fgets(line, sizeof(line), file)) {
        int game_id;
        DiceSet game_sets[100];
        int num_sets = 0;

        char *ptr = strtok(line, ":");
        if (ptr) sscanf(ptr, "Game %d", &game_id);

        ptr = strtok(NULL, ":");
        if (ptr) {
            while ((ptr = strtok(ptr, ";")) != NULL) {
                parse_dice(ptr, &game_sets[num_sets++]);
                ptr = NULL;
            }
        }

        // Check if the game is possible with the given max set of dice
        if (is_possible_game(&max_set, game_sets, num_sets)) {
            possible_sum += game_id;
        }

        // Find the minimum number of each color dice required for the game
        int min_red = 0, min_green = 0, min_blue = 0;
        for (int i = 0; i < num_sets; i++) {
            if (game_sets[i].red > min_red) min_red = game_sets[i].red;
            if (game_sets[i].green > min_green) min_green = game_sets[i].green;
            if (game_sets[i].blue > min_blue) min_blue = game_sets[i].blue;
        }
        power_sum += (long long)min_red * min_green * min_blue;
    }

    fclose(file);

    // Output the results
    printf("Sum of possible game IDs: %d\n", possible_sum);
    printf("Sum of powers of minimum sets: %lld\n", power_sum);

    return 0;
}
