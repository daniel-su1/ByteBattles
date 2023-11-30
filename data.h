#ifndef DATA_H
#define DATA_H

#include "link.h"
class Data: public Link {
    public:
        Data(int strength, Coords currCoords, string displayName, Player &owner);
        int getStrength() override;
        LinkType getType() override;
        bool isIdentityRevealed() override;
        void setStepSize(int newStepSize) override;
        void movePiece(Direction direction) override;
        Coords getPreviousCoords() override;
        Coords getCurrCoords() override;
        void attachPlayer(Player *p) override;
        Player& getOwner() override;
        string getDisplayName() override;
        vector<AbilityCard*>& getAppliedAbilities() override;
};
#endif
