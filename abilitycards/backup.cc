#include "backup.h"

using namespace std;

void BackUp::activate(Link& l) {
    cout << "BOOOMB!!" << endl; 
}

BackUp::BackUp(int abilityID, Player &owner, string displayName):
    AbilityCard(abilityID, owner, displayName, AbilityType::BACKUP, nullptr) {}
