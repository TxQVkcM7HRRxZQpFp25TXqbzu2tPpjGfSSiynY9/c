#include <stdio.h>

typedef struct {
    float x;
    float y;
} Punkt;

typedef struct {
    Punkt lewyGorny;
    Punkt prawyDolny;
} Prostokat;

void zmienWspolrzedne(Punkt *punkt, float noweX, float noweY) {
    punkt->x = noweX;
    punkt->y = noweY;
}

void oblicz(Prostokat prostokat, float *pole, float *obwod) {
    float szerokosc = prostokat.prawyDolny.x - prostokat.lewyGorny.x;
    float wysokosc = prostokat.lewyGorny.y - prostokat.prawyDolny.y;
    *pole = szerokosc * wysokosc;
    *obwod = 2 * (szerokosc + wysokosc);
}

int main() {
    Punkt punkt = {2.5, 3.0};
    zmienWspolrzedne(&punkt, 4.0, 5.5);
    printf("Nowe wspolrzedne punktu: (%.2f, %.2f)\n", punkt.x, punkt.y);

    Prostokat prostokat = {
        {1.0, 4.0},
        {5.0, 1.0}
    };

    float pole, obwod;
    oblicz(prostokat, &pole, &obwod);

    printf("Pole prostokata: %.2f\n", pole);
    printf("Obwod prostokata: %.2f\n", obwod);

    return 0;
}
