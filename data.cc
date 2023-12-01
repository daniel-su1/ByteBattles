#include "data.h"
using namespace std;

Data::Data(int strength, Coords currCoords, string displayName, Player &owner):
    Link{strength, currCoords, displayName, owner, LinkType::data} {}
