#include <stdio.h>

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        int n = array[i];
        int wynik = 1;
        for (int j = 1; j <= n; j++) {
            wynik *= j;
        }
        printf("Silnia z %d: %d\n", n, wynik);
    }

    return 0;
}
