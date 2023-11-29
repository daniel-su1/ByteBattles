#include "gamepiece.h"
GamePiece::GamePiece(Player &owner, string displayName): owner{&owner}, displayName{displayName} {}
void GamePiece::notifyObservers() {
    for (Observer* ob: observers) {
        std::cout << "calling observers" << std::endl;
    }
}
void GamePiece::attach(Observer* ob) {
    observers.emplace_back(ob);
}
void GamePiece::detach(Observer* ob) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (ob == *it) it = observers.erase(it);
        else it++;
    }
}
