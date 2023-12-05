#include "backup.h"
#include "../gameboard.h"

using namespace std;

void BackUp::activate(Link& l) {
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    l.backupStep();
    gb->notifyObservers(l);
}

BackUp::BackUp(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::BACKUP, gb) {}
