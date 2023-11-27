#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#include <string>
#include <vector>
using namespace std;
#include "player.h"
#include "abilitycard.h"

class GamePiece {
    protected:
    // pointer to the player that owns the piece
    Player *owner;
    string displayName;
    vector<AbilityCard*> appliedAbilites;
    public:
    // attaches a player (owner) to the piece
    virtual void attachPlayer(Player *p) = 0;
    // returns a reference to the owner
    virtual Player& getOwner() = 0;
    // returns the display name
    virtual string getDisplayName() = 0;
    // returns the avaliable ability cards
    virtual vector<AbilityCard*>& getAppliedAbilities() = 0;
};

#endif