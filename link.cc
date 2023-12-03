#include "link.h"

Link::Link(int strength, Coords currCoords, string displayName, Player &owner, LinkType type):
    BoardPiece(stepSize, currCoords, owner, displayName),
    strength{strength}, type{type}, identityRevealed{true}, downloaded{false},
    typeAndStrength{((type == LinkType::data) ? "D" : "V") + to_string(strength)} {}

Link::~Link(){}

bool Link::isDownloaded() {
    return downloaded;
}

void Link::setDownloaded(bool d) {
    downloaded = d;
}

bool Link::isIdentityRevealed() { return identityRevealed; }

LinkType Link::getType() { return type; }

int Link::getStrength() { return strength; }

int Link::getStepSize() {
    return stepSize;
}

void Link::setIdentityRevealed(bool b ) {
    identityRevealed = b;
}
