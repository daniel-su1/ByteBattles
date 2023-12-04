#include "firewall.h"
#include "iostream"
using namespace std;

void FireWall::activate() {
    usedAbility = true;
    notifyObservers();
}

void FireWall::setCoords(int x, int y) {
    coords.setX(x);
    coords.setY(y);
}

Coords FireWall::getCoords() {
    return coords;
}

FireWall::FireWall(int abilityID, Player &owner, string displayName): AbilityCard(abilityID, owner, displayName,AbilityType::FIREWALL),coords{Coords(-100,-100)} {};
