#include "hazeofwar.h"

using namespace std;

void HazeOfWar::activate(int x, int y) {
    cout << "HAZEOFWAR!!" << endl; 
}

HazeOfWar::HazeOfWar(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::HAZEOFWAR, nullptr) {}
