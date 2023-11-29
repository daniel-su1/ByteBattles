#include "edgecoord.h"

Coords EdgeCoord::getCoords() {
    return coords;
}

EdgeCoord::EdgeCoord(Coords coords): SpecialCoord(coords) {};