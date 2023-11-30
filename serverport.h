#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "specialcoord.h"

class ServerPort: public SpecialCoord {
    public:
        ServerPort(Coords coords, Player &owner, string displayName = "");
        ~ServerPort() = default;
        virtual void attachPlayer(Player *p) override;
        // returns a reference to the owner
        virtual Player& getOwner() override;
        // returns the display name
        virtual string getDisplayName() override;
        // returns the avaliable ability cards
        virtual vector<AbilityCard*>& getAppliedAbilities() override;
};

#endif

