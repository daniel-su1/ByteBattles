#ifndef HAZEOFWAR_H
#define HAZEOFWAR_H
#include "../abilitycard.h"
class HazeOfWar: public AbilityCard {
    public:
        void activate() override;
        HazeOfWar(int abilityID, Player &owner, string displayName);
};

#endif

