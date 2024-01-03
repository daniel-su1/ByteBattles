#ifndef WALL_H
#define WALL_H
#include "../abilitycard.h"
#include "../coords.h"
#include "../gameboard.h"

class Wall: public AbilityCard {
    Coords coords;
    public:
        void activate(int x, int y) override;
        Coords getCoords();
        Wall(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif

