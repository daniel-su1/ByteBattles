#include "serverport.h"

Coords ServerPort::getCoords() {
    return coords;
}

ServerPort::ServerPort(Coords coords, Player &owner, string displayName): SpecialCoord(coords, owner, displayName) {}
