#ifndef FIREWALL_H
#define FIREWALL_H
#include "../abilitycard.h"
#include "../coords.h"
class FireWall: public AbilityCard {
    Coords coords;
    public:
        void activate() override;
        void setCoords(int xCoord, int yCoord);
        Coords getCoords();
        FireWall(int abilityID, Player &owner, string displayName);
};

#endif
