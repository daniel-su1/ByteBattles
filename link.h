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
        string typeAndStrength;
        // returns the strength of the link
        int getStrength();
        // returns the type of the link
        LinkType getType();
        // returns true/false depending on whether identity of the link is known by the other player
        bool isIdentityRevealed();
        // returns step size
        int getStepSize();
        
        virtual ~Link();
};

#endif