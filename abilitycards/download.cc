#include "download.h"
#include "iostream"
using namespace std;

void Download::activate() {
    cout << "DOWNLOADED!!" << endl;
}

Download::Download(int abilityID, Player &owner, string DisplayName): AbilityCard(abilityID, owner, displayName, abilityType::DOWNLOAD) {}
