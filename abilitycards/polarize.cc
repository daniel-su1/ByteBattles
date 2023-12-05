#include "polarize.h"
#include "../gameboard.h"
#include "../link.h"
#include "../virus.h"
#include "../data.h"

using namespace std;

void Polarize::activate(Link& l) {
    l.polarize(gb->VIRUS_DISPLAY_STR, gb->DATA_DISPLAY_STR);
    LinkType newType = l.getType();
    int prevNumData = owner->getNumDataDownloads();
    int prevNumVirus = owner->getNumVirusDownloads();
    if (l.isDownloaded()) { // update counts for player
        if (newType == LinkType::DATA) {
            owner->setNumDataDownloaded(prevNumData++);
            owner->setNumVirusDownloaded(prevNumVirus--);
        } else {
            owner->setNumDataDownloaded(prevNumData--);
            owner->setNumVirusDownloaded(prevNumVirus++);
        }
    } else {
        for (FireWall fw : gb->getActiveFirewalls()) {
            if ((fw.getCoords().getX() == l.getCurrCoords().getX()) && (fw.getCoords().getY() == l.getCurrCoords().getY())) {
                // must be a data after the polarize
                gb->downloadLink(l, owner);
            }
        }
    }
    usedAbility = true;
    owner->abilityUsed(); // decrease abilityCount for displays
}

Polarize::Polarize(int abilityID, Player &owner, string displayName, GameBoard* gb):
    AbilityCard(abilityID, owner, displayName, AbilityType::POLARIZE, gb) {}
