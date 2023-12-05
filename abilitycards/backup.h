#ifndef BACKUP_H
#define BACKUP_H
#include "../abilitycard.h"

class BackUp: public AbilityCard {
    public:
        void activate(Link& l) override;
        BackUp(int abilityID, Player &owner, string displayName, GameBoard* gb);
};

#endif

