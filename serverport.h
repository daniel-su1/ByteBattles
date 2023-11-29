#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "specialcoord.h"

class ServerPort: public SpecialCoord {
    public:
    Coords getCoords() override;
};

#endif

