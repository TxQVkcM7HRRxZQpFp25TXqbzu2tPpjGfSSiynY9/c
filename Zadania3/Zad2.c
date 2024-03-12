#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **stworzMacierz(int wiersze, int kolumny) {
    int **macierz = (int **)malloc(wiersze * sizeof(int *));
    if (macierz == NULL) {
        printf("Błąd alokacji pamięci!\n");
        exit(1);
    }

    for (int i = 0; i < wiersze; i++) {
        macierz[i] = (int *)malloc(kolumny * sizeof(int));
        if (macierz[i] == NULL) {
            printf("Błąd alokacji pamięci!\n");
            exit(1);
        }
        for (int j = 0; j < kolumny; j++) {
            macierz[i][j] = rand() % 100;
        }
    }
    return macierz;
}

void wyswietlMacierz(int **macierz, int wiersze, int kolumny) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            printf("%d ", macierz[i][j]);
        }
        printf("\n");
    }
}

void zwolnijMacierz(int **macierz, int wiersze) {
    for (int i = 0; i < wiersze; i++) {
        free(macierz[i]);
    }
    free(macierz);
}

int main() {
    int wiersze, kolumny;

    printf("Podaj liczbe wierszy macierzy: ");
    scanf("%d", &wiersze);
    printf("Podaj liczbe kolumn macierzy: ");
    scanf("%d", &kolumny);

    srand(time(NULL));

    int **macierz = stworzMacierz(wiersze, kolumny);

    printf("Wygenerowana macierz:\n");
    wyswietlMacierz(macierz, wiersze, kolumny);

    zwolnijMacierz(macierz, wiersze);

    return 0;
}
