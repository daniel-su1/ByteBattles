#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "../abilitycard.h"
class Download: public AbilityCard {
    public:
    void activate(Link& l) override;
    Download(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif
