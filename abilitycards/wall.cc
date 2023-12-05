#include "wall.h"
#include "../gameboard.h"

using namespace std;

void Wall::activate(int x, int y) {
    coords.setX(x);
    coords.setY(y);
    usedAbility = true;
    owner->abilityUsed();  // decrease abilityCount for displays
    gb->addWall(*this);
}

Coords Wall::getCoords() { return coords; }

Wall::Wall(int abilityID, Player& owner, string displayName, GameBoard* gb)
    : AbilityCard(abilityID, owner, displayName, AbilityType::WALL, gb) {}

