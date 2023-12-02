#include "gamepiece.h"

GamePiece::GamePiece(Player &owner, string displayName): owner{&owner}, displayName{displayName}, appliedAbilites() {
}

vector<AbilityCard*>& GamePiece::getAppliedAbilities() { return appliedAbilites; }

string GamePiece::getDisplayName() { return displayName; }

Player& GamePiece::getOwner() {
    return *owner;
}

void GamePiece::attachPlayer(Player* p) { owner = p; }

void GamePiece::notifyObservers() {
    for (Observer* ob: observers) {
        std::cout << "calling observers" << std::endl;
    }
}