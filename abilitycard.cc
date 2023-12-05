#include "abilitycard.h"

AbilityCard::AbilityCard(int abilityID, Player &owner, string displayName, AbilityType type, GameBoard* gb): GamePiece(owner, displayName),
    abilityID{abilityID}, cardType{type}, usedAbility{false}, gb{gb} {}

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
    throw (logic_error("AC setCoords error: this should not run"));
}

// for others
void AbilityCard::attachToLink(Link& l) {
    throw (logic_error("AC attachToLink error: this should not run"));
}
