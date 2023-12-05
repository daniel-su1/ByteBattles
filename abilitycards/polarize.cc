#include "polarize.h"
#include "../gameboard.h"
#include "../link.h"
#include "../virus.h"
#include "../data.h"

using namespace std;

void Polarize::activate(Link& l) {
    l.polarize(gb->VIRUS_DISPLAY_STR, gb->DATA_DISPLAY_STR);
    gb->notifyObservers(); // TODO: fix notify
}

Polarize::Polarize(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::POLARIZE, gb) {}
