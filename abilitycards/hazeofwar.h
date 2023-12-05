#ifndef HAZEOFWAR_H
#define HAZEOFWAR_H
#include "../abilitycard.h"
class HazeOfWar: public AbilityCard {
    public:
        void activate(int x, int y) override;
        HazeOfWar(int abilityID, Player &owner, string displayName);
};

#endif

