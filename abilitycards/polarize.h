#ifndef POLARIZE_H
#define POLARIZE_H
#include "../abilitycard.h"
class Polarize: public AbilityCard {
    public:
        void activate() override;
        Polarize(int abilityID, Player &owner, string DisplayName);
};

#endif

