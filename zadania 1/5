#include <stdio.h>

int main() {
    int liczba;
    printf("Podaj liczbę: ");
    scanf("%d", &liczba);

    if (liczba < 0) {
        printf("Suma wielokrotności 3 lub 5 poniżej podanej liczby wynosi: 0\n");
    } else {
        int suma = 0;
        for (int i = 3; i < liczba; i++) {
            if (i % 3 == 0 || i % 5 == 0) {
                suma += i;
            }
        }
        printf("Suma wielokrotności 3 lub 5 poniżej %d wynosi: %d\n", liczba, suma);
    }

    return 0;
}
