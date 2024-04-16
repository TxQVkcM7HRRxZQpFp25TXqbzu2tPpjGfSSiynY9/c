#include <stdio.h>

// Definicja unii zawierającej pola różnych typów danych
union Dane {
    int calkowita;
    float zmiennoprzecinkowa;
    char znak;
};

int main() {
    // Deklaracja unii
    union Dane Unia;

    // Przechowywanie wartości całkowitej i wyświetlenie
    Unia.calkowita = 10;
    printf("Wartość całkowita: %d\n", Unia.calkowita);

    // Przechowywanie wartości zmiennoprzecinkowej i wyświetlenie
    Unia.zmiennoprzecinkowa = 3.14;
    printf("Wartość zmiennoprzecinkowa: %f\n", Unia.zmiennoprzecinkowa);

    // Przechowywanie znaku i wyświetlenie
    Unia.znak = 'A';
    printf("Znak: %c\n", Unia.znak);

    return 0;
}
