#include "link.h"

Link::Link(int strength, Coords currCoords, string displayName, Player &owner, LinkType type):
BoardPiece(stepSize, currCoords, owner, displayName),
strength{strength}, type{type}, identityRevealed{false} {}

Link::~Link(){}
