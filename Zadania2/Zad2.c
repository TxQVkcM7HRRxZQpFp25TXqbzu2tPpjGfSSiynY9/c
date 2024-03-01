#include <stdio.h>

void modyfikuj(float *ptr) {
    *ptr *= 2;
}

int main() {
    float zmienna = 3.5;
    modyfikuj(&zmienna);
    printf("Nowa wartość zmiennej: %.2f\n", zmienna);
    return 0;
}
