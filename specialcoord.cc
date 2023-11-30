#include "specialcoord.h"
#include "coords.h"

SpecialCoord::SpecialCoord(Coords coords, Player &owner, string displayName): GamePiece(owner, displayName),coords{coords} {}

Coords SpecialCoord::getCoords() {
    return coords;
}