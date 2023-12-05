#include "wall.h"

using namespace std;

void Wall::activate(Link& l) {
    
}

Wall::Wall(int abilityID, Player& owner, string displayName)
    : AbilityCard(abilityID, owner, displayName, AbilityType::WALL,
                  nullptr) {}
