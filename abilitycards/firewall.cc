#include "firewall.h"
#include "../gameboard.h"

using namespace std;

void FireWall::activate(int x, int y) {
    // use values
    coords.setX(x);
    coords.setY(y);
    // try to implement
    gb->addFireWall(*this);
    // update self
    usedAbility = true;
    owner->abilityUsed();  // decrease abilityCount for displays
}

Coords FireWall::getCoords() {
    return coords;
}

FireWall::FireWall(int abilityID, Player &owner, string displayName, GameBoard* gb): 
    AbilityCard(abilityID, owner, displayName,AbilityType::FIREWALL, gb) {}
