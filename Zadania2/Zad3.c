#include <stdio.h>

struct Point {
    float x;
    float y;
};

void zmienWspolrzedne(struct Point *p, float nowyX, float nowyY) {
    p->x = nowyX;
    p->y = nowyY;
}

struct Rectangle {
    struct Point topleft;
    struct Point bottomright;
};

float poleProstokata(struct Rectangle *rect) {
    float szerokosc = rect->bottomright.x - rect->topleft.x;
    float wysokosc = rect->topleft.y - rect->bottomright.y;
    return szerokosc * wysokosc;
}

float obwodProstokata(struct Rectangle *rect) {
    float szerokosc = rect->bottomright.x - rect->topleft.x;
    float wysokosc = rect->topleft.y - rect->bottomright.y;
    return 2 * (szerokosc + wysokosc);
}

int main() {
    struct Point punkt = {2.5, 3.5};
    zmienWspolrzedne(&punkt, 5.0, 7.0);
    printf("Nowe współrzędne punktu: (%.2f, %.2f)\n", punkt.x, punkt.y);
    struct Rectangle prostokat = {{1.0, 4.0}, {6.0, 1.0}};
    printf("Pole prostokąta: %.2f\n", poleProstokata(&prostokat));
    printf("Obwód prostokąta: %.2f\n", obwodProstokata(&prostokat));

    return 0;
}
