#include "polarize.h"
#include "iostream"
using namespace std;

void Polarize::activate() {
    cout << "Polarized beep!!" << endl; 
}

Polarize::Polarize(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, abilityType::POLARIZE) {}
