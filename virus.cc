#include "virus.h"
using namespace std;

Virus::Virus(int strength) : Link{strength, virus} {}

int Virus::getStrength() {
    return strength;
}

LinkType Virus::getType() {
    return type;
}

bool Virus::isIdentityRevealed() {
    return identityRevealed;
}

