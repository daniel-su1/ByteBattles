#include "coords.h"
Coords::Coords(int x, int y): x{x}, y{y} {
}
int Coords::getX() {
    return x;
}

int Coords::getY() {
    return y;
}

Coords::Coords(int x, int y) {
    setX(x);
    setY(y);
}

void Coords::setX(int newX) {
    x = newX;
}

void Coords::setY(int newY) {
    y = newY;
}


