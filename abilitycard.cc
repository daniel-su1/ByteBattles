#include "abilitycard.h"

AbilityCard::AbilityCard(int abilityID, Player &owner, string displayName, AbilityType type): GamePiece(owner, displayName),
    usedAbility{false}, abilityID{abilityID}, cardType{type} {}

AbilityType AbilityCard::getType() {
    return cardType;
}

bool AbilityCard::isUsed() {
    return usedAbility;
}

int AbilityCard::getAbilityId() {
    return abilityID;
}

