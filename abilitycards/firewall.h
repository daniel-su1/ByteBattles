#ifndef FIREWALL_H
#define FIREWALL_H
#include "abilitycard.h"
#include "coords.h"

class Firewall : public AbilityCard {
    Coords coords;

   public:
    Coords getCoords();
    void activate();
}

#endif
