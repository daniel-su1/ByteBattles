#include "virus.h"
using namespace std;

Virus::Virus(int strength) : Link{strength, LinkType::virus} {}

int Virus::getStrength() {
    return strength;
}

LinkType Virus::getType() {
    return type;
}

bool Virus::isIdentityRevealed() {
    return identityRevealed;
}

void Virus::setStepSize(int newStepSize) {
    stepSize = newStepSize;
}
void Virus::movePiece(Direction direction) {
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

Coords Virus::getPreviousCoords() {
    return prevCords;  
}

Coords Virus:: getCurrCoords() {
    return currCoords;
}

void Virus::attachPlayer(Player *p) {
    owner = p;
}

Player& Virus::getOwner() {
    return *owner;
}

string Virus::getDisplayName() {
    return displayName;
}

vector<AbilityCard*>& Virus::getAppliedAbilities() {
    return appliedAbilites;
}

