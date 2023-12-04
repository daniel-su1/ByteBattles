#include "polarize.h"

using namespace std;

void Polarize::activate() {
    cout << "Polarized beep!!" << endl; 
}

Polarize::Polarize(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::POLARIZE, nullptr) {}
