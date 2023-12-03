#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#include <string>
#include <iostream>
#include <vector>
#include "player.h"
#include "subject.h"

class AbilityCard;
using namespace std;
class GamePiece: public Subject {
    protected:
        // pointer to the player that owns the piece
        Player *owner;
        string displayName;
        vector<AbilityCard&> appliedAbilites;
    public:
        GamePiece(Player &owner, string displayName);
        // attaches a player (owner) to the piece
        void attachPlayer(Player *p);
        // attaches an ability to the piece's appliedAbilities
        void abilityApplied(AbilityCard& ability);
        // returns a reference to the owner
        Player& getOwner();
        // returns the display name
        string getDisplayName();
        // returns the avaliable ability cards
        vector<AbilityCard&>& getAppliedAbilities();
        void notifyObservers() override;
};

#endif