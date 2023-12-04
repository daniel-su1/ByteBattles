#include "wallwall.h"
#include "iostream"
using namespace std;

void WallWall::activate() {
    cout << "WALL WALL!!" << endl; 
}

WallWall::WallWall(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::WALLWALL, nullptr) {}
