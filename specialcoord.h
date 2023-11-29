#ifndef SPECIALCOORD_H
#define SPECIALCOORD_H
#include "coords.h"
class SpecialCoord {
    protected:
    Coords coords;
    public:
    SpecialCoord(Coords coords);
    virtual Coords getCoords() = 0;
};

#endif
