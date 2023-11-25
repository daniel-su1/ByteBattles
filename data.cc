#include "data.h"
using namespace std;

Data::Data(int strength) : Link{strength, data} {}

int Data::getStrength() {
    return strength;
}

LinkType Data::getType() {
    return type;
}

bool Data::isIdentityRevealed() {
    return identityRevealed;
}
