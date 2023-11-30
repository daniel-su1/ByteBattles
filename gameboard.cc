#include "gameboard.h"

GameBoard::GameBoard(): td{nullptr}, players(), allBoardPieces(), allAbilityCards(),
    currPlayer{nullptr}, winner{nullptr}, boardBoundaries(), edgeCoords(),
    serverPorts(), activeFirewalls() {}

GameBoard::~GameBoard() {
    delete td;
}

void GameBoard::notifyObservers() {

}

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

    td = new TextDisplay;

    for (int i = 1; i <= PLAYER_COUNT; i++) {
        string playerName = "Player " + to_string(i);
        int abilityCount = ABILITY_COUNT;
        players.emplace_back(Player(playerName, abilityCount));
    }

    currPlayer = &(players[0]);

    // for (int playerNum = 1; playerNum <= PLAYER_COUNT; playerNum++) {
    //     for (int i = 0; i < BOARD_SIZE; i++) {
    //         // waiting on abilitycards.cc ctor
    //         // owner: players[playerNum - 1]
    //         // allBoardPieces.emplace_back();
    //     }
    // }

    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 1; i < BOARD_SIZE - 1; i++) {
            boardBoundaries.emplace_back(Coords(0 - stepSize, i)); 
            boardBoundaries.emplace_back(Coords(BOARD_SIZE - 1 + stepSize, i)); 
        }
    }

    // for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
    //     for (int i = 0; i < BOARD_SIZE; i++) {
    //         // waiting on edgecoord.cc ctor
    //         // edgeCoords.emplace_back(Edgecoord(Coords(i, 0 - stepSize)), attach player somehow); // winning positions for one player
    //         // edgeCoords.emplace_back coords(i, BOARD_SIZE - 1 + stepSize), still attach player // winning positions for other player
    //     }
    //     // edgeCoords.emplace_back coords (0 - stepSize, 0)
    //     // (0 - stepSize, BOARD_SIZE - 1)
    //     // (BOARD_SIZE - 1 + stepSize, 0)
    //     // (BOARD_SIZE - 1 + stepsize, BOARD_SIZE - 1)
    // }

    // serverPorts.emplace_back(Coords(BOARD_SIZE / 2 - 1, 0));
    // serverPorts.emplace_back(Coords(BOARD_SIZE / 2, 0));
    // serverPorts.emplace_back(Coords(BOARD_SIZE / 2 - 1, BOARD_SIZE - 1));
    // serverPorts.emplace_back(Coords(BOARD_SIZE / 2, BOARD_SIZE - 1));
}

void GameBoard::setAbilities(string abilities, Player *player) {
    cout << "abilities for " << player->getPlayerName() << " set" << endl;
    cout << "abilities order: " << abilities << endl;
    // TODO: create ability cards and set them in the gameboard
    // also handle bad input and throw it out maybe
    // or just deal with it lmao but maybe still cerr
}

void GameBoard::setLinks(unique_ptr <vector<string>> linkPlacements, Player *player) {
    cout << "links for " << player->getPlayerName() << " set" << endl;
    cout << "links placements: ";
    for (auto link : *linkPlacements) {
        cout << link << " ";
    }
    cout << endl;
    // TODO: create links and set in gb, handle bad input
}

vector<Player>& GameBoard::getPlayers() {
    return players;
}

ostream &operator<<(ostream &out, const GameBoard &gb) {
    cout << *gb.td << endl;
    return out;
}

