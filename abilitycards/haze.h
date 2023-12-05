#ifndef HAZE_H
#define HAZE_H
#include "../abilitycard.h"
class Haze: public AbilityCard {
    public:
        void activate(int x, int y) override;
        Haze(int abilityID, Player &owner, string displayName);
};

#endif

