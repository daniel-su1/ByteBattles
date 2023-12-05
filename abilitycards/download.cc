#include "download.h"

using namespace std;

void Download::activate(Link& l) {
    cout << "DOWNLOADED!!" << endl;
}

Download::Download(int abilityID, Player &owner, string displayName): 
    AbilityCard(abilityID, owner, displayName, AbilityType::DOWNLOAD, nullptr) {}
