#ifndef BOMB_H
#define BOMB_H
#include "../abilitycard.h"
class Bomb: public AbilityCard {
    public:
        void activate() override;
        Bomb(int abilityID, Player &owner, string displayName);
};

#endif

