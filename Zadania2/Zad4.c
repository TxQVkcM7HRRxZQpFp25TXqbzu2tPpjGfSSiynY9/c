#include <stdio.h>
#include <string.h>

struct Student {
    char imie[50];
    float ocena;
};

void sortujStudentow(struct Student *tablica, int rozmiar) {
    int i, j;
    struct Student temp;

    for (i = 0; i < rozmiar - 1; i++) {
        for (j = 0; j < rozmiar - i - 1; j++) {
            if (tablica[j].ocena < tablica[j + 1].ocena) {
                // Zamiana miejscami
                temp = tablica[j];
                tablica[j] = tablica[j + 1];
                tablica[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct Student studenci[] = {
        {"Anna", 4.5},
        {"Jan", 3.7},
        {"Katarzyna", 4.9},
        {"Piotr", 3.2},
        {"Zofia", 5.0}
    };
    int rozmiar = sizeof(studenci) / sizeof(studenci[0]);
    sortujStudentow(studenci, rozmiar);
    printf("Posortowana lista studentow:\n");
    for (int i = 0; i < rozmiar; i++) {
        printf("%s - %.2f\n", studenci[i].imie, studenci[i].ocena);
    }

    return 0;
}
