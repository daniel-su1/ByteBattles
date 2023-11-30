#include "serverport.h"

ServerPort::ServerPort(Coords coords, Player &owner, string displayName): SpecialCoord(coords, owner, displayName) {}

void ServerPort::attachPlayer(Player *p) {
    owner = p;
}

Player& ServerPort::getOwner(){
    return *owner;
}

string ServerPort::getDisplayName() {
    return displayName;
}

vector<AbilityCard*>& ServerPort::getAppliedAbilities() {
    return appliedAbilites; 
}
