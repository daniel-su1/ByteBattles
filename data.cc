#include "data.h"
using namespace std;

Data::Data(int strength, Coords currCoords, string displayName, Player &owner, string typeAndStrength):
    Link{strength, currCoords, displayName, owner, LinkType::data, typeAndStrength} {}
