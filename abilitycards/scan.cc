#include "scan.h"

using namespace std;

void Scan::activate(Link& l) {
    cout << "scaaaan!!" << endl; 
}

Scan::Scan(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::SCAN, nullptr) {}
