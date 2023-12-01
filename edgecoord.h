#ifndef EDGECOORD_H
#define EDGECOORD_H
#include "specialcoord.h"

class EdgeCoord: public SpecialCoord {
    public:
        EdgeCoord(Coords coords, Player &owner, string displayName);
        ~EdgeCoord() = default;
};

#endif

