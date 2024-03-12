#include <stdio.h>
#include <stdlib.h>

int wspolczynnikDwumianowy(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return wspolczynnikDwumianowy(n - 1, k - 1) + wspolczynnikDwumianowy(n - 1, k);
}

void wyswietlTrojkatPascala(int wysokosc) {
    int **trojkat = (int **)malloc(wysokosc * sizeof(int *));
    if (trojkat == NULL) {
        printf("Błąd alokacji pamięci!\n");
        exit(1);
    }

    for (int i = 0; i < wysokosc; i++) {
        trojkat[i] = (int *)malloc((i + 1) * sizeof(int));
        if (trojkat[i] == NULL) {
            printf("Błąd alokacji pamięci!\n");
            exit(1);
        }

        for (int j = 0; j <= i; j++) {
            trojkat[i][j] = wspolczynnikDwumianowy(i, j);
        }
    }

    for (int i = 0; i < wysokosc; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", trojkat[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < wysokosc; i++) {
        free(trojkat[i]);
    }
    free(trojkat);
}

int main() {
    int N;
    printf("Podaj wysokość trójkąta Pascala: ");
    scanf("%d", &N);

    printf("Trójkąt Pascala o wysokości %d:\n", N);
    wyswietlTrojkatPascala(N);

    return 0;
}
