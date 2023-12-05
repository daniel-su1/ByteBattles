#include "link.h"

Link::Link(int strength, Coords currCoords, string displayName, Player &owner, LinkType type, string typeAndStrength):
    BoardPiece(stepSize, currCoords, owner, displayName), downloader{nullptr},
    strength{strength}, type{type}, identityRevealed{false}, downloaded{false},
    typeAndStrength{typeAndStrength} {}

Link::~Link(){}

bool Link::isDownloaded() {
    return downloaded;
}

Player& Link::getDownloader() {
    return *downloader;
}

void Link::setDownloaded(bool d) {
    downloaded = d;
}

void Link::setStepSize(int stepSize) {
    this->stepSize = stepSize;
}

void Link::polarize(string virusStr, string dataStr) {
    if (type == LinkType::DATA) {
        type = LinkType::VIRUS;
        typeAndStrength[0] = virusStr[0];
    } else { // must be a data type
        type = LinkType::DATA;
        typeAndStrength[0] = dataStr[0];
    }
}

void Link::attachDownloader(Player* p) { downloader = p; }

bool Link::isIdentityRevealed() { return identityRevealed; }

LinkType Link::getType() { return type; }

int Link::getStrength() { return strength; }

int Link::getStepSize() {
    return stepSize;
}

void Link::setIdentityRevealed(bool b) {
    identityRevealed = b;
}
