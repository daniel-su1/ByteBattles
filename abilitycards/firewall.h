#ifndef FIREWALL_H
#define FIREWALL_H
#include "../abilitycard.h"
#include "../coords.h"
class FireWall: public AbilityCard {
    Coords coords;
    public:
    void activate() override;
    Coords getCoords();
};

#endif

