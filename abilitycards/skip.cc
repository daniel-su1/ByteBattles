#include "skip.h"
#include "../gameboard.h"

using namespace std;

void Skip::activate(Link& l) { 
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    gb->startNewTurn();
}

Skip::Skip(int abilityID, Player &owner, string displayName, GameBoard* gb)
    : AbilityCard(abilityID, owner, displayName, AbilityType::SKIP, gb) {}
