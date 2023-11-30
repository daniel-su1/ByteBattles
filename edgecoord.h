#ifndef EDGECOORD_H
#define EDGECOORD_H
#include "specialcoord.h"

class EdgeCoord: public SpecialCoord {
    public:
        EdgeCoord(Coords coords, Player &owner, string displayName);
        ~EdgeCoord() = default;
        virtual void attachPlayer(Player *p) override;
        // returns a reference to the owner
        virtual Player& getOwner() override;
        // returns the display name
        virtual string getDisplayName() override;
        // returns the avaliable ability cards
        virtual vector<AbilityCard*>& getAppliedAbilities() override;
};

#endif

