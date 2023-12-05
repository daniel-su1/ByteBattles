#include "hazeofwar.h"

using namespace std;

void HazeOfWar::activate(int x, int y) {
    cout << "HAZEOFWAR!!" << endl; 
}

Coords HazeOfWar::getCoords() {
    return coords;
}

HazeOfWar::HazeOfWar(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::HAZEOFWAR, gb),
    coords{Coords(-100,-100)} {}
