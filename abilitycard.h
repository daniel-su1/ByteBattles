#ifndef ABILITYCARD_H
#define ABILITYCARD_H
#include "gamepiece.h"

class Link;
class GameBoard;

enum AbilityType {LINKBOOST, FIREWALL, DOWNLOAD, POLARIZE, SCAN, WALLWALL, BOMB, HAZEOFWAR};

class AbilityCard: public GamePiece {
    int abilityID;
    AbilityType cardType;
    protected:
        bool usedAbility;
        GameBoard* gb;
    public:
        AbilityCard(int abilityID, Player &owner, string displayName, AbilityType type, GameBoard* gb);
        AbilityType getType();
        bool isUsed();
        int getAbilityId();
        virtual void activate(int x, int y); // for firewall, wallwall, and hazeofwar
        virtual void activate(Link& l); // for others
};

#endif
