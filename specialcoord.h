#ifndef SPECIALCOORD_H
#define SPECIALCOORD_H
#include "coords.h"
#include "gamepiece.h"
class SpecialCoord: public GamePiece {
    protected:
        Coords coords;
    public:
        SpecialCoord(Coords coords, Player &owner, string displayName);
        virtual Coords getCoords() = 0;
};

#endif
