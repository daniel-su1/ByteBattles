#include "scan.h"
#include "iostream"
using namespace std;

void Scan::activate() {
    cout << "scaaaan!!" << endl; 
}

Scan::Scan(int abilityID, Player &owner, string DisplayName):
    AbilityCard(abilityID, owner, displayName, abilityType::scan) {}
