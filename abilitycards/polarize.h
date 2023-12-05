#ifndef POLARIZE_H
#define POLARIZE_H
#include "../abilitycard.h"

class Polarize: public AbilityCard {
    public:
        void activate(Link& l) override;
        Polarize(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif

