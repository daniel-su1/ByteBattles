#ifndef WALL_H
#define WALL_H
#include "../abilitycard.h"
class Wall: public AbilityCard {
    public:
        void activate(Link& l) override;
        Wall(int abilityID, Player &owner, string displayName);
};

#endif

