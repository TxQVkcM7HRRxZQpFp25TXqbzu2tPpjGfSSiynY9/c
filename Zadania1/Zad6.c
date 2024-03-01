#include <stdio.h>

int main() {

    while (1) {
        printf("\nTwój ruch (0 - kamień, 1 - papier, 2 - nożyce): ");
        int ruch_gracza;
        scanf("%d", &ruch_gracza);

        int ruch_komputera = rand() % 3;
        printf("Ruch komputera: %d\n", ruch_komputera);

        if (ruch_gracza == ruch_komputera) {
            printf("Remis\n");
        } else if ((ruch_gracza == 0 && ruch_komputera == 2) ||
                   (ruch_gracza == 1 && ruch_komputera == 0) ||
                   (ruch_gracza == 2 && ruch_komputera == 1)) {
            printf("Gracz wygrywa\n");
        } else {
            printf("Komputer wygrywa\n");
        }
    }

    return 0;
}
