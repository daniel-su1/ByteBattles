#ifndef ABILITYCARD_H
#define ABILITYCARD_H
#include "gamepiece.h"

enum abilityType {firewall, scan, polarize, download, linkboost};

class AbilityCard: public GamePiece {
    bool usedAbility;
    int abilityID;
    abilityType cardType;
    public:
        AbilityCard(int abilityID, Player &owner, string DisplayName, abilityType type);
        abilityType getType();
        virtual bool isUsed() = 0;
        virtual int getAbilityId() = 0;
        virtual void activate() = 0; // TO DO: implement all the activate() functions for diff cards
};
#endif

