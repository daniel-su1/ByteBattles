#include "edgecoord.h"

Coords EdgeCoord::getCoords() {
    return coords;
}

EdgeCoord::EdgeCoord(Coords coords, Player &owner, string displayName): SpecialCoord(coords, owner, displayName) {};