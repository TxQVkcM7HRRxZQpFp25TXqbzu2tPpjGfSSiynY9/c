#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    int num;
    printf("Podaj liczbę całkowitą: ");
    scanf("%d", &num);
    printf("Silnia z %d = %d\n", num, factorial(num));
    return 0;
}
