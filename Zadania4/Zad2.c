#include <stdio.h>

int wyszukiwanieBinarne(int tablica[], int lewy, int prawy, int x) {
    if (prawy >= lewy) {
        int srodek = lewy + (prawy - lewy) / 2;

        if (tablica[srodek] == x)
            return srodek;

        if (tablica[srodek] > x)
            return wyszukiwanieBinarne(tablica, lewy, srodek - 1, x);

        return wyszukiwanieBinarne(tablica, srodek + 1, prawy, x);
    }
    return -1;
}

int main(void) {
    int tablica[] = {2, 3, 4, 10, 40};
    int n = sizeof(tablica) / sizeof(tablica[0]);
    int x = 10;
    int wynik = wyszukiwanieBinarne(tablica, 0, n - 1, x);
    (wynik == -1) ? printf("Element nie został znaleziony w tablicy.\n")
                   : printf("Element znajduje się pod indeksem %d.\n", wynik);
    return 0;
}
