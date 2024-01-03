#include "wall.h"
#include "../gameboard.h"

using namespace std;

void Wall::activate(int x, int y) {
    coords.setX(x);
    coords.setY(y);
    gb->addWall(*this);
    usedAbility = true;
    owner->abilityUsed();  // decrease abilityCount for displays
}

Coords Wall::getCoords() { return coords; }

Wall::Wall(int abilityID, Player& owner, string displayName, GameBoard* gb)
    : AbilityCard(abilityID, owner, displayName, AbilityType::WALL, gb) {}

