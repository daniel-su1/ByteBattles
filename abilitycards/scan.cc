#include "scan.h"
#include "../gameboard.h"

using namespace std;

void Scan::activate(Link& l) {
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    gb->revealIdentity(l);
}

Scan::Scan(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::SCAN, gb) {}
