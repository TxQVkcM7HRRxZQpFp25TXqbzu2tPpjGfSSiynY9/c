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

void drukuj_liste(struct Element* element) {
    while (element != NULL) {
        printf("%d ", element->dane);
        element = element->nastepny;
    }
    printf("\n");
}

int main() {
    struct Element* glowa = NULL;
    
    add_first(&glowa, 3);
    add_first(&glowa, 5);
    add_first(&glowa, 7);
    
    drukuj_liste(glowa);
    
    return 0;
}
