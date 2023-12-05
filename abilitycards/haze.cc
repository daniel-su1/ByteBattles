#include "haze.h"

using namespace std;

void Haze::activate(int x, int y) { cout << "HAZE!!" << endl; }

Haze::Haze(int abilityID, Player &owner, string displayName)
    : AbilityCard(abilityID, owner, displayName, AbilityType::HAZE, nullptr) {}
