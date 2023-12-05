#ifndef NEXTTURN_H
#define NEXTTURN_H

#include "../abilitycard.h"

class NextTurn: public AbilityCard {
    public:
    void activate(Link& l) override;
    NextTurn(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif
