#include "coords.h"
Coords::Coords(int x, int y): x{x}, y{y} {}
Coords::Coords(){}

int Coords::getX() {
    return x;
}

int Coords::getY() {
    return y;
}

void Coords::setX(int newX) {
    x = newX;
}

void Coords::setY(int newY) {
    y = newY;
}

bool Coords::operator==(Coords& rhs) {
    return x == rhs.getX() && y == rhs.getY();
}
