#ifndef LINKBOOST_H
#define LINKBOOST_H
#include "../abilitycard.h"
class LinkBoost: public AbilityCard {
    public:
        void activate() override;
        LinkBoost(int abilityID, Player &owner, string displayName);
};

#endif

