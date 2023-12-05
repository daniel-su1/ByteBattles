#include "movetwice.h"
#include "../gameboard.h"

using namespace std;

void MoveTwice::activate() { 
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    gb->enableMoveTwice();
}

MoveTwice::MoveTwice(int abilityID, Player &owner, string displayName, GameBoard* gb)
    : AbilityCard(abilityID, owner, displayName, AbilityType::MOVETWICE, gb) {}
