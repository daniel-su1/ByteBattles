#ifndef VIRUS_H
#define VIRUS_H

#include "link.h"
class Virus: public Link {
    public:
    Virus(int strength);
    int getStrength() override;
    LinkType getType() override;
    bool isIdentityRevealed() override;
    void setStepSize(int newStepSize) override;
    void movePiece(Direction direction) override;
    Coords getPreviousCoords() override;
    Coords getCurrCoords() override;
};

#endif