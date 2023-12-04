#ifndef ABILITYCARD_H
#define ABILITYCARD_H
#include "gamepiece.h"

enum AbilityType {LINKBOOST, FIREWALL, DOWNLOAD, POLARIZE, SCAN, WALLWALL, BOMB, HAZEOFWAR};

class AbilityCard: public GamePiece {
    bool usedAbility;
    int abilityID;
    AbilityType cardType;
    public:
        AbilityCard(int abilityID, Player &owner, string displayName, AbilityType type);
        AbilityType getType();
        bool isUsed();
        int getAbilityId();
        virtual void activate() = 0; // TO DO: implement all the activate() functions for diff cards
};

#endif
