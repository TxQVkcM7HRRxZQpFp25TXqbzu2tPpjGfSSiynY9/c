#include <stdio.h>

int main() {
    int oceny[2][5] = {
        {2, 2, 3, 2, 4},
        {3, 5, 4, 5, 2}
    };

    double srednia_matematyka = 0.0, srednia_fizyka = 0.0;
    for (int i = 0; i < 5; i++) {
        srednia_matematyka += oceny[0][i];
        srednia_fizyka += oceny[1][i];
    }
    srednia_matematyka /= 5;
    srednia_fizyka /= 5;

    printf("Średnia ocen z matematyki: %.2f\n", srednia_matematyka);
    printf("Średnia ocen z fizyki: %.2f\n", srednia_fizyka);

    return 0;
}
