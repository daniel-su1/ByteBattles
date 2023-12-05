#ifndef SKIP_H
#define SKIP_H

#include "../abilitycard.h"
class Skip: public AbilityCard {
    public:
    void activate(Link& l) override;
    Skip(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif
