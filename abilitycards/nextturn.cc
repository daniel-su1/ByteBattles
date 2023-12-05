#include "nextturn.h"
#include "../gameboard.h"

using namespace std;

void NextTurn::activate(Link& l) { 
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    gb->startNewTurn();
}

NextTurn::NextTurn(int abilityID, Player &owner, string displayName, GameBoard* gb)
    : AbilityCard(abilityID, owner, displayName, AbilityType::NEXTTURN, gb) {}
