#include "data.h"
using namespace std;

Data::Data(int strength) : Link{strength, data} {}

int Data::getStrength() {
    return strength;
}

LinkType Data::getType() {
    return type;
}

bool Data::isIdentityRevealed() {
    return identityRevealed;
}

void Data::setStepSize(int newStepSize) {
    stepSize = newStepSize;
}

void Data::movePiece(Direction direction) {
    prevCords = currCoords;
    if (direction == Left) { // TODO: implement checking for moves
        int newX = currCoords.getX() - stepSize;
        currCoords.setX(newX);
    } else if (direction == Right) {
        int newX = currCoords.getX() + stepSize;
        currCoords.setX(newX);
    } else if (direction == Up) {
        int newY = currCoords.getY() + stepSize;
        currCoords.setY(newY);
    } else if (direction == Down) {
        int newY = currCoords.getY() - stepSize;
        currCoords.setY(newY);
    }
}

Coords Data::getPreviousCoords() {
    return prevCords;  
}

Coords Data::getCurrCoords() {
    return currCoords;
}
