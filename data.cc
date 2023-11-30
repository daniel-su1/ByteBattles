#include "data.h"
using namespace std;

Data::Data(int strength, Coords currCoords, string displayName, Player &owner):
Link{strength, currCoords, displayName, owner, LinkType::data} {}

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

void Data::attachPlayer(Player *p) {
    owner = p;
}

Player& Data::getOwner() {
    return *owner;
}

string Data::getDisplayName() {
    return displayName;
}

vector<AbilityCard*>& Data::getAppliedAbilities() {
    return appliedAbilites;
}
