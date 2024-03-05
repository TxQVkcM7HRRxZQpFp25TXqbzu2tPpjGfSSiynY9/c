#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100

typedef struct {
    char imie[50];
    char nazwisko[50];
    char numer_telefonu[20];
} Kontakt;

Kontakt ksiazka_adresowa[MAX_CONTACTS];
int liczba_kontaktow = 0;

void dodajKontakt() {
    if (liczba_kontaktow < MAX_CONTACTS) {
        printf("Podaj imie: ");
        scanf("%s", ksiazka_adresowa[liczba_kontaktow].imie);
        printf("Podaj nazwisko: ");
        scanf("%s", ksiazka_adresowa[liczba_kontaktow].nazwisko);
        printf("Podaj numer telefonu: ");
        scanf("%s", ksiazka_adresowa[liczba_kontaktow].numer_telefonu);
        liczba_kontaktow++;
        printf("Kontakt dodany.\n");
    } else {
        printf("Ksiazka adresowa jest pelna.\n");
    }
}

void wyszukajKontaktPoNazwisku(char *nazwisko) {
    int znaleziono = 0;
    for (int i = 0; i < liczba_kontaktow; i++) {
        if (strcmp(ksiazka_adresowa[i].nazwisko, nazwisko) == 0) {
            printf("Imie: %s, Nazwisko: %s, Numer telefonu: %s\n", ksiazka_adresowa[i].imie, ksiazka_adresowa[i].nazwisko, ksiazka_adresowa[i].numer_telefonu);
            znaleziono = 1;
        }
    }
    if (!znaleziono) {
        printf("Kontakt o nazwisku %s nie zostal znaleziony.\n", nazwisko);
    }
}

void usunKontaktPoNazwisku(char *nazwisko) {
    int indeks_do_usuniecia = -1;
    for (int i = 0; i < liczba_kontaktow; i++) {
        if (strcmp(ksiazka_adresowa[i].nazwisko, nazwisko) == 0) {
            indeks_do_usuniecia = i;
            break;
        }
    }
    if (indeks_do_usuniecia != -1) {
        for (int i = indeks_do_usuniecia; i < liczba_kontaktow - 1; i++) {
            ksiazka_adresowa[i] = ksiazka_adresowa[i + 1];
        }
        liczba_kontaktow--;
        printf("Kontakt o nazwisku %s zostal usuniety.\n", nazwisko);
    } else {
        printf("Kontakt o nazwisku %s nie zostal znaleziony.\n", nazwisko);
    }
}

void wyswietlWszystkieKontakty() {
    printf("Ksiazka adresowa:\n");
    for (int i = 0; i < liczba_kontaktow; i++) {
        printf("Imie: %s, Nazwisko: %s, Numer telefonu: %s\n", ksiazka_adresowa[i].imie, ksiazka_adresowa[i].nazwisko, ksiazka_adresowa[i].numer_telefonu);
    }
}

int main() {
    int wybor;
    char nazwisko[50];

    do {
        printf("\nWybierz opcje:\n");
        printf("1. Dodaj kontakt\n");
        printf("2. Znajdz kontakt po nazwisku\n");
        printf("3. Usun kontakt po nazwisku\n");
        printf("4. Wyswietl wszystkie kontakty\n");
        printf("5. Wyjdz\n");
        printf("Wybor: ");
        scanf("%d", &wybor);

        switch (wybor) {
            case 1:
                dodajKontakt();
                break;
            case 2:
                printf("Podaj nazwisko: ");
                scanf("%s", nazwisko);
                wyszukajKontaktPoNazwisku(nazwisko);
                break;
            case 3:
                printf("Podaj nazwisko: ");
                scanf("%s", nazwisko);
                usunKontaktPoNazwisku(nazwisko);
                break;
            case 4:
                wyswietlWszystkieKontakty();
                break;
            case 5:
                printf("Koniec programu.\n");
                break;
            default:
                printf("Niepoprawny wybor. Wybierz ponownie.\n");
        }
    } while (wybor != 5);

    return 0;
}
