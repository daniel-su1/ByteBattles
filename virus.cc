#include "virus.h"
using namespace std;

Virus::Virus(int strength, Coords currCoords, string displayName, Player &owner, string typeAndStrength):
    Link{strength, currCoords, displayName, owner, LinkType::VIRUS, typeAndStrength} {}

