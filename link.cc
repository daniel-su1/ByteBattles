#include "link.h"

Link::Link(int strength, Coords currCoords, string displayName, Player &owner, LinkType type, string typeAndStrength):
    BoardPiece(stepSize, currCoords, owner, displayName),
    strength{strength}, type{type}, identityRevealed{false}, downloaded{false},
    typeAndStrength{typeAndStrength} {}

Link::~Link(){}

bool Link::isDownloaded() {
    return downloaded;
}

void Link::setDownloaded(bool d) {
    downloaded = d;
}

void Link::setStepSize(int stepSize) {
    stepSize = stepSize;
}

bool Link::isIdentityRevealed() { return identityRevealed; }

LinkType Link::getType() { return type; }

int Link::getStrength() { return strength; }

int Link::getStepSize() {
    return stepSize;
}

void Link::setIdentityRevealed(bool b) {
    identityRevealed = b;
}
