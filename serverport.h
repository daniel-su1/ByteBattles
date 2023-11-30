#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "specialcoord.h"

class ServerPort: public SpecialCoord {
    public:
        ServerPort(Coords coords, Player &owner, string displayName);
        Coords getCoords() override;
};

#endif

