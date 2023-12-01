#include "firewall.h"
#include "iostream"
using namespace std;

void FireWall::activate() {
    cout << "FIREWALL WOOSH" << endl; 
}

Coords FireWall::getCoords() {
    return coords;
}

FireWall::FireWall(int abilityID, Player &owner, string DisplayName): AbilityCard(abilityID, owner, displayName,abilityType::firewall),coords{Coords(-1,-1)} {};
