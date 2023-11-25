#include "link.h"

Link::Link(int strength, LinkType type) : strength{strength}, type{type}, identityRevealed{false} {};

Link::~Link(){};