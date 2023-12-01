#include "polarize.h"
#include "iostream"
using namespace std;

void Polarize::activate() {
    cout << "Polarized beep!!" << endl; 
}

Polarize::Polarize(int abilityID, Player &owner, string DisplayName):
    AbilityCard(abilityID, owner, displayName, abilityType::polarize) {}
