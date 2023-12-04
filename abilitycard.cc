#include "abilitycard.h"

AbilityCard::AbilityCard(int abilityID, Player &owner, string displayName, AbilityType type): GamePiece(owner, displayName),
    abilityID{abilityID}, cardType{type}, usedAbility{false} {}

AbilityType AbilityCard::getType() {
    return cardType;
}

bool AbilityCard::isUsed() {
    return usedAbility;
}

int AbilityCard::getAbilityId() {
    return abilityID;
}

// default impl for non-firewall, wallwall, or hazeofwar
void AbilityCard::setCoords(int x, int y) {
    cerr << "AC setCoords error: this should not run" << endl;
}

// for others
void AbilityCard::attachToPlayer(Player& p) {
    cerr << "AC attachToPlayer error: this should not run" << endl;
}