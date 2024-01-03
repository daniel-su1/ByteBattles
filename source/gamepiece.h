#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#include <string>
#include <iostream>
#include <vector>
#include "player.h"

class AbilityCard;
using namespace std;
class GamePiece {
    protected:
        // pointer to the player that owns the piece
        Player *owner;
        string displayName;
    public:
        GamePiece(Player &owner, string displayName);
        // returns a reference to the owner
        Player& getOwner();
        // returns the display name
        string getDisplayName();
};

#endif
