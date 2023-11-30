#include "boardpiece.h"

BoardPiece::BoardPiece(int stepSize, Coords currCoords, Player& owner, string displayName): 
    GamePiece(owner, displayName), 
    stepSize{stepSize}, prevCords(Coords(-1, -1)), currCoords(currCoords) {}
