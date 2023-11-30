#include "abilitycard.h"

AbilityCard::AbilityCard(int abilityID, Player &owner, string DisplayName): GamePiece(owner, displayName),
    usedAbility{false}, abilityID{abilityID} {}

