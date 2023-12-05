#include "scan.h"
#include "../gameboard.h"

using namespace std;

void Scan::activate(Link& l) {
    bool toggleLink = false;
    // scanning your own 
    if (l.getOwner().getPlayerName() == gb->getPlayers()[gb->getCurrPlayerIndex()]->getPlayerName()) {
        toggleLink = true;
    }
    gb->revealIdentity(l, toggleLink);
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
}

Scan::Scan(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::SCAN, gb) {}
