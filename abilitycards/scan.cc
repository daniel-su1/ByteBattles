#include "scan.h"
#include "iostream"
using namespace std;

void Scan::activate() {
    cout << "scaaaan!!" << endl; 
}

Scan::Scan(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::SCAN, nullptr) {}
