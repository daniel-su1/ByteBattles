#include "bomb.h"
#include "iostream"
using namespace std;

void Bomb::activate() {
    cout << "BOOOMB!!" << endl; 
}

Bomb::Bomb(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::BOMB, nullptr) {}
