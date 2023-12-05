#ifndef MOVETWICE_H
#define MOVETWICE_H

#include "../abilitycard.h"

class MoveTwice: public AbilityCard {
    public:
    void activate() override;
    MoveTwice(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif
