#ifndef WALLWALL_H
#define WALLWALL_H
#include "../abilitycard.h"
class WallWall: public AbilityCard {
    public:
        void activate() override;
        WallWall(int abilityID, Player &owner, string displayName);
};

#endif

