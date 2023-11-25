#ifndef VIRUS_H
#define VIRUS_H

#include "link.h"
class Virus: public Link {
    public:
    Virus(int strength);
    int getStrength() override;
    LinkType getType() override;
    bool isIdentityRevealed() override;
};

#endif