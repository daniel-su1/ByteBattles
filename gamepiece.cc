#include "gamepiece.h"
void GamePiece::notifyObservers() {
    for (Observer* ob: observers) {
        std::cout << "calling observers" << std::endl;
    }
}
