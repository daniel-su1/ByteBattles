#include "gameboard.h"

GameBoard::GameBoard(): td{nullptr}, players(), allBoardPieces(), allAbilityCards(),
    currPlayer{nullptr}, winner{nullptr}, boardBoundaries(), edgeCoords(),
    serverPorts(), activeFirewalls() {}

GameBoard::~GameBoard() {}

void GameBoard::init() {
    // reset
    td = nullptr;
    players.clear();
    allBoardPieces.clear();
    allAbilityCards.clear();
    currPlayer = nullptr;
    winner = nullptr;
    boardBoundaries.clear();
    edgeCoords.clear();
    serverPorts.clear();
    activeFirewalls.clear();

    // set defaults
    const int BOARD_SIZE = 8;
    const int MAX_STEPSIZE = 2;
    const int PLAYER_COUNT = 2;
    const int ABILITY_COUNT = 5;

    td = make_unique<TextDisplay>();

    for (int i = 0; i < PLAYER_COUNT; i++) {
        string playerName = "Player " + i;
        int numVirusDownloaded = 0;
        int numDataDownloaded = 0;
        int abilityCount = ABILITY_COUNT;
        bool won = false;
        players.emplace_back(Player(playerName, numVirusDownloaded, numDataDownloaded, abilityCount, won));
    }
    currPlayer = make_unique<Player>(players[0]);

    for (int i = 0; i < BOARD_SIZE; i++) {
        // waiting on boardpiece.cc ctor implementation
        // allBoardPieces.emplace_back();
    }

    for (int i = 0; i < ABILITY_COUNT; i++) {
        // waiting on abilitycards.cc ctor
        // allAbilityCards.emplace_back();
    }

    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 1; i < BOARD_SIZE - 1; i++) {
            boardBoundaries.emplace_back(Coords(0 - stepSize, i)); // left side
            boardBoundaries.emplace_back(Coords(BOARD_SIZE - 1 + stepSize, i)); // right side
        }
    }

    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            // waiting on edgecoord.cc ctor
            // edgeCoords.emplace_back(Edgecoord(Coords(i, 0 - stepSize)), attach player somehow); // winning positions for one player
            // edgeCoords.emplace_back coords(i, BOARD_SIZE - 1 + stepSize), still attach player // winning positions for other player
        }
        // edgeCoords.emplace_back coords (0 - stepSize, 0)
        // (0 - stepSize, BOARD_SIZE - 1)
        // (BOARD_SIZE - 1 + stepSize, 0)
        // (BOARD_SIZE - 1 + stepsize, BOARD_SIZE - 1)
    }

    serverPorts.emplace_back(Coords(BOARD_SIZE / 2 - 1, 0));
    serverPorts.emplace_back(Coords(BOARD_SIZE / 2, 0));
    serverPorts.emplace_back(Coords(BOARD_SIZE / 2 - 1, BOARD_SIZE - 1));
    serverPorts.emplace_back(Coords(BOARD_SIZE / 2, BOARD_SIZE - 1));
}

ostream &operator<<(ostream &out, const GameBoard &gb) {
    cout << *gb.td << endl;
    return out;
}

