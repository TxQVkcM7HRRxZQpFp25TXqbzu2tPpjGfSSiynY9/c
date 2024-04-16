#include <stdio.h>

int main() {
    // Tworzenie tablicy dziesięciu liczb całkowitych i inicjalizacja jej wartościami od 0 do 9
    int tablica[10];
    for (int i = 0; i < 10; i++) {
        tablica[i] = i;
    }

    // Używanie wskaźnika do wyświetlenia każdego elementu tablicy
    int *wskaznik = tablica; // Inicjalizacja wskaźnika na pierwszy element tablicy

    printf("Zawartość tablicy:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", *wskaznik); // Wyświetlenie wartości wskazywanej przez wskaźnik
        wskaznik++; // Przesunięcie wskaźnika na kolejny element tablicy
    }
    printf("\n");

    return 0;
}
