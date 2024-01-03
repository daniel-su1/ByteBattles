#include "polarize.h"
#include "../gameboard.h"
#include "../link.h"
#include "../virus.h"
#include "../data.h"

using namespace std;

void Polarize::activate(Link& l) {
    l.polarize(gb->VIRUS_DISPLAY_STR, gb->DATA_DISPLAY_STR);
    LinkType prevType = l.getType();
    if (l.isDownloaded()) { // update counts for player
        int numData = l.getDownloader().getNumDataDownloads();
        int numVirus = l.getDownloader().getNumVirusDownloads();
        if (prevType == LinkType::DATA) {
            numData++;
            numVirus--;
            l.getDownloader().setNumDataDownloaded(numData);
            l.getDownloader().setNumVirusDownloaded(numVirus);
        } else {
            numData--;
            numVirus++;
            l.getDownloader().setNumDataDownloaded(numData);
            l.getDownloader().setNumVirusDownloaded(numVirus);
        }
        gb->notifyObservers();
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
