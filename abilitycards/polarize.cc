#include "polarize.h"
#include "../gameboard.h"
#include "../link.h"
#include "../virus.h"
#include "../data.h"

using namespace std;

void Polarize::activate(Link& l) {
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    l.polarize(gb->VIRUS_DISPLAY_STR, gb->DATA_DISPLAY_STR);
    gb->notifyObservers(); // TODO: fix notify
}

Polarize::Polarize(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::POLARIZE, gb) {}
