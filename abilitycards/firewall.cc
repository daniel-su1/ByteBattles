#include "firewall.h"
#include "iostream"
using namespace std;

void FireWall::activate() {
    cout << "FIREWALL WOOSH" << endl; 
}

Coords FireWall::getCoords() {
    return coords;
}

FireWall::FireWall(int abilityID, Player &owner, string displayName): AbilityCard(abilityID, owner, displayName,abilityType::FIREWALL),coords{Coords(-100,-100)} {};
