#include "download.h"
#include "iostream"
using namespace std;

void Download::activate() {
    cout << "DOWNLOADED!!" << endl;
}

Download::Download(int abilityID, Player &owner, string displayName): 
    AbilityCard(abilityID, owner, displayName, AbilityType::DOWNLOAD, nullptr) {}
