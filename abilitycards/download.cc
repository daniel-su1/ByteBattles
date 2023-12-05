#include "download.h"
#include "../gameboard.h"

using namespace std;

void Download::activate(Link& l) {
    gb->downloadLink(l);
}

Download::Download(int abilityID, Player &owner, string displayName, GameBoard* gb): 
    AbilityCard(abilityID, owner, displayName, AbilityType::DOWNLOAD, gb) {}
