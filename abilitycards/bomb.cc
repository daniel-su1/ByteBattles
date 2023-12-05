#include "bomb.h"

using namespace std;

void Bomb::activate(Link& l) {
    cout << "BOOOMB!!" << endl; 
}

Bomb::Bomb(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::BOMB, nullptr) {}
