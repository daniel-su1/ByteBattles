#include "linkboost.h"

using namespace std;

void LinkBoost::activate() {
    cout << "Link boost!!" << endl; 
}

LinkBoost::LinkBoost(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::LINKBOOST, nullptr) {}
