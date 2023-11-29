#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "specialcoord.h"

class ServerPort: public SpecialCoord {
    public:
    ServerPort(Coords coords);
    Coords getCoords() override;
};

#endif

