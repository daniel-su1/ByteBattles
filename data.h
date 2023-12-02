#ifndef DATA_H
#define DATA_H

#include "link.h"
class Data: public Link {
    public:
        Data(int strength, Coords currCoords, string displayName, Player &owner);
};
#endif
