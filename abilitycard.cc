#include "abilitycard.h"

AbilityCard::AbilityCard(int abilityID, Player &owner, string displayName, abilityType type): GamePiece(owner, displayName),
    usedAbility{false}, abilityID{abilityID}, cardType{type} {}

abilityType AbilityCard::getType() {
    return cardType;
}

bool AbilityCard::isUsed() {
    return usedAbility;
}

int AbilityCard::getAbilityId() {
    return abilityID;
}

