#ifndef HAZEOFWAR_H
#define HAZEOFWAR_H
#include "../abilitycard.h"
#include "../coords.h"

class HazeOfWar: public AbilityCard {
    Coords coords;
    public:
        void activate(int x, int y) override;
        Coords getCoords();
        HazeOfWar(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif
