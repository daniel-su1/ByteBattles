#include "polarize.h"

using namespace std;

void Polarize::activate(Link& l) {
    cout << "Polarized beep!!" << endl; 
}

Polarize::Polarize(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::POLARIZE, nullptr) {}
