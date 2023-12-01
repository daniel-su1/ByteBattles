#ifndef VIRUS_H
#define VIRUS_H

#include "link.h"
class Virus: public Link {
    public:
        Virus(int strength, Coords currCoords, string displayName, Player &owner);
};
#endif
