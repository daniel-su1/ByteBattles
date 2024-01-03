#include "linkboost.h"
#include "../link.h"

using namespace std;

LinkBoost::LinkBoost(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::LINKBOOST, nullptr) {}

void LinkBoost::activate(Link& l) {
    l.setStepSize(2);
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
}
