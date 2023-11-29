#include "gameboard.h"

GameBoard::GameBoard(): td{nullptr}, players(), allBoardPieces(), allAbilityCards(),
    currPlayer{nullptr}, winner{nullptr}, boardBoundaries(), edgeCoords(),
    serverPorts(), activeFirewalls() {}

GameBoard::~GameBoard() {}

void GameBoard::init() {
    td = nullptr;
    players.clear();
    allBoardPieces.clear();
    allAbilityCards.clear();
    boardBoundaries.clear();
    edgeCoords.clear();
    serverPorts.clear();
    activeFirewalls.clear();
    td = make_unique<TextDisplay>();
    // adding the server ports
    serverPorts.emplace_back(Coords(3,0));
    serverPorts.emplace_back(Coords(4,0));
    serverPorts.emplace_back(Coords(3,7));
    serverPorts.emplace_back(Coords(4,7));
    // adding the boundary pieces
    

}

ostream &operator<<(ostream &out, const GameBoard &gb) {
    cout << *gb.td << endl;
    return out;
}

