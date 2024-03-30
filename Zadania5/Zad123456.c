#include <stdio.h>
#include <stdlib.h>

struct Element {
    int dane;
    struct Element* nastepny;
};

void add_first(struct Element** glowa_ref, int nowe_dane) {
    struct Element* nowy_element = (struct Element*)malloc(sizeof(struct Element));
    if (nowy_element == NULL) {
        printf("Błąd alokacji pamięci\n");
        return;
    }
    
    nowy_element->dane = nowe_dane;
    
    nowy_element->nastepny = *glowa_ref;
    
    *glowa_ref = nowy_element;
}

void pop(struct Element** glowa_ref) {
    if (*glowa_ref == NULL) {
        printf("Lista jest pusta, nie ma elementów do usunięcia.\n");
        return;
    }
    
    struct Element* temp = *glowa_ref;
    *glowa_ref = (*glowa_ref)->nastepny;
    free(temp);
}

void remove_last(struct Element** glowa_ref) {
    if (*glowa_ref == NULL) {
        printf("Lista jest pusta, nie ma elementów do usunięcia.\n");
        return;
    }

    if ((*glowa_ref)->nastepny == NULL) {
        free(*glowa_ref);
        *glowa_ref = NULL;
        return;
    }

    struct Element* obecny = *glowa_ref;
    while (obecny->nastepny->nastepny != NULL) {
        obecny = obecny->nastepny;
    }

    free(obecny->nastepny);
    obecny->nastepny = NULL;
}

void remove_by_index(struct Element** glowa_ref, int index) {
    if (*glowa_ref == NULL) {
        printf("Lista jest pusta, nie ma elementów do usunięcia.\n");
        return;
    }

    struct Element* obecny = *glowa_ref;
    struct Element* poprzedni = NULL;

    if (index == 0) {
        *glowa_ref = obecny->nastepny;
        free(obecny);
        return;
    }

    for (int i = 0; obecny != NULL && i < index; i++) {
        poprzedni = obecny;
        obecny = obecny->nastepny;
    }

    if (obecny == NULL) {
        printf("Podany indeks przekracza długość listy.\n");
        return;
    }

    poprzedni->nastepny = obecny->nastepny;
    free(obecny);
}

void remove_by_value(struct Element** glowa_ref, int wartosc) {
    if (*glowa_ref == NULL) {
        printf("Lista jest pusta, nie ma elementów do usunięcia.\n");
        return;
    }

    struct Element* obecny = *glowa_ref;
    struct Element* poprzedni = NULL;

    if (obecny != NULL && obecny->dane == wartosc) {
        *glowa_ref = obecny->nastepny;
        free(obecny);
        return;
    }

    while (obecny != NULL && obecny->dane != wartosc) {
        poprzedni = obecny;
        obecny = obecny->nastepny;
    }

    if (obecny == NULL) {
        printf("Nie znaleziono elementu o wartości %d w liście.\n", wartosc);
        return;
    }

    poprzedni->nastepny = obecny->nastepny;
    free(obecny);
}

void add_by_index(struct Element** glowa_ref, int index, int nowe_dane) {
    struct Element* nowy_element = (struct Element*)malloc(sizeof(struct Element));
    if (nowy_element == NULL) {
        printf("Błąd alokacji pamięci\n");
        return;
    }
    
    nowy_element->dane = nowe_dane;
    
    if (index == 0 || *glowa_ref == NULL) {
        nowy_element->nastepny = *glowa_ref;
        *glowa_ref = nowy_element;
        return;
    }

    struct Element* temp = *glowa_ref;
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->nastepny;
    }

    if (temp == NULL) {
        printf("Podany indeks przekracza długość listy.\n");
        return;
    }

    nowy_element->nastepny = temp->nastepny;
    temp->nastepny = nowy_element;
}

void drukuj_liste(struct Element* element) {
    while (element != NULL) {
        printf("%d ", element->dane);
        element = element->nastepny;
    }
    printf("\n");
}

int main() {
    struct Element* glowa = NULL;
    
    printf("1. Dodanie elementów na początek listy:\n");
    add_first(&glowa, 6);
    add_first(&glowa, 5);
    add_first(&glowa, 5);
    add_first(&glowa, 4);
    add_first(&glowa, 3);
    add_first(&glowa, 2);
    add_first(&glowa, 1);
    drukuj_liste(glowa);
    printf("\n");

    printf("2. Usunięcie pierwszego elementu z listy:\n");
    pop(&glowa);
    drukuj_liste(glowa);
    printf("\n");

    printf("3. Usunięcie ostatniego elementu z listy:\n");
    remove_last(&glowa);
    drukuj_liste(glowa);
    printf("\n");

    printf("4. Usunięcie elementu z listy na indeksie 1:\n");
    remove_by_index(&glowa, 1);
    drukuj_liste(glowa);
    printf("\n");

    printf("5. Usunięcie pierwszego elementu z wartością 5:\n");
    remove_by_value(&glowa, 5);
    drukuj_liste(glowa);
    printf("\n");

    printf("6. Dodanie elementu o wartości 3 na indeksie 1:\n");
    add_by_index(&glowa, 1, 3);
    drukuj_liste(glowa);
    printf("\n");

    return 0;
}
