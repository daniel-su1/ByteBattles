#ifndef ABILITYCARD_H
#define ABILITYCARD_H
#include "gamepiece.h"

class AbilityCard: public GamePiece {
    bool usedAbility;
    int abilityID;
    public:
        AbilityCard(int abilityID, Player &owner, string DisplayName);
        virtual bool isUsed() = 0;
        virtual int getAbilityId() = 0;
        virtual void activate() = 0; // TO DO: implement all the activate() functions for diff cards
};
#endif
