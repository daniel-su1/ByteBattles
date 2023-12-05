#ifndef SCAN_H
#define SCAN_H
#include "../abilitycard.h"
class Scan: public AbilityCard {
    public:
        void activate(Link& l) override;
        Scan(int abilityID, Player &owner, string displayName);
};

#endif

