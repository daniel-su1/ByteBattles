#ifndef LINK_H
#define LINK_H

#include "boardpiece.h"
enum LinkType {data, virus};

class Link: public BoardPiece{
    protected:
        int strength;  
        LinkType type;
        bool identityRevealed;
        Link(int strength, Coords currCoords, string displayName, Player &owner, LinkType type);
    public:
        // returns the strength of the link
        virtual int getStrength() = 0;
        // returns the type of the link
        virtual LinkType getType() = 0;
        // returns true/false depending on whether identity of the link is known by the other player
        virtual bool isIdentityRevealed() = 0;
        virtual ~Link();
};

#endif