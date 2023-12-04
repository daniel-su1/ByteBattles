#ifndef ABILITYCARD_H
#define ABILITYCARD_H
#include "gamepiece.h"

enum AbilityType {LINKBOOST, FIREWALL, DOWNLOAD, POLARIZE, SCAN, WALLWALL, BOMB, HAZEOFWAR};

class AbilityCard: public GamePiece {
    int abilityID;
    AbilityType cardType;
    protected:
        bool usedAbility;
    public:
        AbilityCard(int abilityID, Player &owner, string displayName, AbilityType type);
        AbilityType getType();
        bool isUsed();
        int getAbilityId();
        virtual void activate() = 0;
        virtual void setCoords(int x, int y); // for firewall, wallwall, and hazeofwar
        virtual void attachToPlayer(Player& p); // for others
};

#endif
