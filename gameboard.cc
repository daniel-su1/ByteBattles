#include "gameboard.h"

GameBoard::GameBoard(): td{nullptr}, players(), allBoardPieces(), allAbilityCards(),
    currPlayer{nullptr}, winner{nullptr}, boardBoundaries(), edgeCoords(),
    serverPorts(), activeFirewalls() {}

GameBoard::~GameBoard() {
    delete td;
}

ostream &operator<<(ostream &out, const GameBoard &gb) {
    cout << *gb.td << endl;
    return out;
}

void GameBoard::notifyObservers() { td->notify(*this); }

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
    string SP_DISPLAY_STR = "S";
    string BORDER_DISPLAY_STR = "=";

    td = new TextDisplay;

    // intialize players
    for (int i = 1; i <= PLAYER_COUNT; i++) {
        string playerName = "Player " + to_string(i);
        int abilityCount = ABILITY_COUNT;
        players.emplace_back(Player(playerName, abilityCount));
    }
    
    // intialize server ports; middle of board
    serverPorts.emplace_back(ServerPort(Coords(0, BOARD_SIZE / 2 - 1), players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(0, BOARD_SIZE / 2), players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(BOARD_SIZE - 1, BOARD_SIZE / 2 - 1), players[1], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(BOARD_SIZE - 1, BOARD_SIZE / 2), players[1], SP_DISPLAY_STR));
    currPlayer = &(players[0]);

    // adding board boundaries based on board sizes
    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            boardBoundaries.emplace_back(Coords(0 - stepSize, i)); 
            boardBoundaries.emplace_back(Coords(BOARD_SIZE - 1 + stepSize, i)); 
        }
    }

    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if ((i != BOARD_SIZE / 2) && (i != BOARD_SIZE /2 - 1)) {
             // player 2's target/winning areas
            edgeCoords.emplace_back(EdgeCoord(Coords(i, 0 - stepSize), players[1], BORDER_DISPLAY_STR)); 
             // player 1's target/winning areas
            edgeCoords.emplace_back(EdgeCoord(Coords(i, BOARD_SIZE - 1 + stepSize), players[0], BORDER_DISPLAY_STR));
            }
        }
    }
    notifyObservers();
}

optional<string> GameBoard::moveLink(string linkName, string direction) {
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        return "i am a movelink error message";
    } else {
        return {};
    }
}

string GameBoard::playerAbilities(Player& player) {
    return "these are my abilities yahoo";
}

optional<string> GameBoard::useAbility(int abilityID) {
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        return "i am a useability error message";
    } else {
        return {};
    }
}

optional<string> GameBoard::useAbility(int abilityID, string linkName) { // for link boost
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        return "i am a useability for link boosts error message";
    } else {
        return {};
    }
}

optional<string> GameBoard::useAbility(int abilityId, int xCoord, int yCoord) { // for firewall
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        return "i am a useability for firewalls error message";
    } else {
        return {};
    }
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

void GameBoard::setAbilities(string abilities, Player *player) {
    cout << "abilities for " << player->getPlayerName() << " set" << endl;
    cout << "abilities order: " << abilities << endl;
    // TODO: create ability cards and set them in the gameboard
    // also handle bad input and throw it out maybe
    // or just deal with it lmao but maybe still cerr
}

vector<Player>& GameBoard::getPlayers() {
    return players;
}

Player& GameBoard::getCurrPlayer() {
    return *currPlayer;
}

vector<ServerPort>& GameBoard::getServerPort() {
    return serverPorts;
}
