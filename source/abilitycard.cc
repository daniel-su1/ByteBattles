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

// default impl for non-firewall or wall
void AbilityCard::activate(int x, int y) {
    throw (logic_error("AC activate on x and y error: this should not run"));
}

// movetwice
void AbilityCard::activate() {
    throw (logic_error("AC activate error: this should not run"));
}

// for others
void AbilityCard::activate(Link& l) {
    throw (logic_error("AC active on link error: this should not run"));
}
