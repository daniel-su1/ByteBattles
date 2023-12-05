#include "linkboost.h"
#include "../link.h"

using namespace std;

void LinkBoost::activate() {
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
    
}

LinkBoost::LinkBoost(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::LINKBOOST, nullptr) {}

void LinkBoost::attachToLink(Link& l) {
    l.setStepSize(2);
}
