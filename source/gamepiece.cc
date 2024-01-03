#include "gamepiece.h"

GamePiece::GamePiece(Player &owner, string displayName): owner{&owner}, displayName{displayName} {}

string GamePiece::getDisplayName() { return displayName; }

Player& GamePiece::getOwner() {
    return *owner;
}

