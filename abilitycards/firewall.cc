#include "firewall.h"
#include "../gameboard.h"

using namespace std;

void FireWall::activate(int x, int y) {
    coords.setX(x);
    coords.setY(y);
    gb->addFireWall(*this);
    usedAbility = true;
    owner->abilityUsed();  // decrease abilityCount for displays
}

Coords FireWall::getCoords() {
    return coords;
}

FireWall::FireWall(int abilityID, Player &owner, string displayName, GameBoard* gb): 
    AbilityCard(abilityID, owner, displayName,AbilityType::FIREWALL, gb) {}
