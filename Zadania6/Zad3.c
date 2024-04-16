#include <stdio.h>

// Deklaracje funkcji
int dodawanie(int a, int b);
int mnozenie(int a, int b);
int odejmowanie(int a, int b);

int main() {
    // Deklaracja wskaźnika do funkcji
    int (*wskaznikFunkcji)(int, int);

    int a, b;
    char operacja;

    printf("Podaj pierwszą liczbę: ");
    scanf("%d", &a);
    printf("Podaj drugą liczbę: ");
    scanf("%d", &b);

    printf("Wybierz operację:\n");
    printf("a) Dodawanie\n");
    printf("b) Mnożenie\n");
    printf("c) Odejmowanie\n");
    scanf(" %c", &operacja);

    // Ustawienie wskaźnika na odpowiednią funkcję w zależności od wyboru użytkownika
    switch (operacja) {
        case 'a':
            wskaznikFunkcji = dodawanie;
            break;
        case 'b':
            wskaznikFunkcji = mnozenie;
            break;
        case 'c':
            wskaznikFunkcji = odejmowanie;
            break;
        default:
            printf("Błąd: Niepoprawny wybór operacji.\n");
            return 1;
    }

    // Wywołanie funkcji za pomocą wskaźnika i wyświetlenie wyniku
    int wynik = wskaznikFunkcji(a, b);
    printf("Wynik: %d\n", wynik);

    return 0;
}

// Definicje funkcji
int dodawanie(int a, int b) {
    return a + b;
}

int mnozenie(int a, int b) {
    return a * b;
}

int odejmowanie(int a, int b) {
    return a - b;
}
