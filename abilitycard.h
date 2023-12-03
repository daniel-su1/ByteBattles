#ifndef ABILITYCARD_H
#define ABILITYCARD_H
#include "gamepiece.h"

enum abilityType {FIREWALL, SCAN, POLARIZE, DOWNLOAD, LINKBOOST};

class AbilityCard: public GamePiece {
    bool usedAbility;
    int abilityID;
    abilityType cardType;
    public:
        AbilityCard(int abilityID, Player &owner, string displayName, abilityType type);
        abilityType getType();
        bool isUsed();
        int getAbilityId();
        virtual void activate() = 0; // TO DO: implement all the activate() functions for diff cards
};
#endif

