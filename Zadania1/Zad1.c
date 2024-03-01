#include <stdio.h>

int main() {
    char name[100];

    printf("Wpisz swoje imię: ");

    scanf("%s", name);

    printf("Witaj, %s!\n", name);

    return 0;
}
