#ifndef FIREWALL_H
#define FIREWALL_H
#include "../abilitycard.h"
#include "../coords.h"

class FireWall: public AbilityCard {
    Coords coords;
    public:
        void activate() override;
        void setCoords(int x, int y) override;
        Coords getCoords();
        FireWall(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif
