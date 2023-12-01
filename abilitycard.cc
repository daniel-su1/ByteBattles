#include "abilitycard.h"

AbilityCard::AbilityCard(int abilityID, Player &owner, string DisplayName, abilityType type): GamePiece(owner, displayName),
    usedAbility{false}, abilityID{abilityID}, cardType{type} {}

abilityType AbilityCard::getType() {
    return cardType;
}


