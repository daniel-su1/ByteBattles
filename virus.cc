#include "virus.h"
using namespace std;

Virus::Virus(int strength, Coords currCoords, string displayName, Player &owner):
    Link{strength, currCoords, displayName, owner, LinkType::virus} {}

    