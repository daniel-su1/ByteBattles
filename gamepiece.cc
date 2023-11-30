#include "gamepiece.h"
GamePiece::GamePiece(Player &owner, string displayName): owner{&owner}, displayName{displayName}, appliedAbilites() {}

void GamePiece::notifyObservers() {
    for (Observer* ob: observers) {
        std::cout << "calling observers" << std::endl;
    }
}
