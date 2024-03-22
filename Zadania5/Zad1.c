#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    int wartosc;
    struct Element* nastepny;
} Element;

void add_first(Element** glowa, int wartosc) {
    Element* nowy_element = (Element*)malloc(sizeof(Element));
    if (nowy_element == NULL) {
        printf("Błąd alokacji pamięci\n");
        exit(EXIT_FAILURE);
    }
    nowy_element->wartosc = wartosc;
    nowy_element->nastepny = *glowa;
    *glowa = nowy_element;
}

void wyswietl_liste(Element* glowa) {
    Element* aktualny = glowa;
    while (aktualny != NULL) {
        printf("%d -> ", aktualny->wartosc);
        aktualny = aktualny->nastepny;
    }
    printf("NULL\n");
}

void zwolnij_liste(Element* glowa) {
    Element* aktualny = glowa;
    while (aktualny != NULL) {
        Element* temp = aktualny;
        aktualny = aktualny->nastepny;
        free(temp);
    }
}

int main() {
    Element* glowa = NULL;

    add_first(&glowa, 3);
    add_first(&glowa, 7);
    add_first(&glowa, 11);

    printf("Lista: ");
    wyswietl_liste(glowa);

    zwolnij_liste(glowa);

    return 0;
}
