#include "firewall.h"
#include "iostream"
using namespace std;

void FireWall::activate() {
    cout << "FIREWALL WOOSH" << endl; 
}

void FireWall::setCoords(int xCoord, int yCoord) {
    coords.setX(xCoord);
    coords.setY(yCoord);
}

Coords FireWall::getCoords() {
    return coords;
}

FireWall::FireWall(int abilityID, Player &owner, string displayName): AbilityCard(abilityID, owner, displayName,AbilityType::FIREWALL),coords{Coords(-100,-100)} {};
