#include "edgecoord.h"

EdgeCoord::EdgeCoord(Coords coords, Player &owner, string displayName): SpecialCoord(coords, owner, displayName) {}

void EdgeCoord::attachPlayer(Player *p) {
    owner = p;
}

Player& EdgeCoord::getOwner(){
    return *owner;
}

string EdgeCoord::getDisplayName() {
    return displayName;
}

vector<AbilityCard*>& EdgeCoord::getAppliedAbilities() {
    return appliedAbilites; 
}
