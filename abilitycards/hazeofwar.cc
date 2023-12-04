#include "hazeofwar.h"
#include "iostream"
using namespace std;

void HazeOfWar::activate() {
    cout << "HAZEOFWAR!!" << endl; 
}

HazeOfWar::HazeOfWar(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::HAZEOFWAR, nullptr) {}
