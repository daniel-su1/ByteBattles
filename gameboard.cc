#include "gameboard.h"
#include "virus.h"
#include "data.h"
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
    serverPorts.emplace_back(ServerPort(Coords(BOARD_SIZE / 2 - 1, 0), players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(BOARD_SIZE / 2, 0), players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(BOARD_SIZE / 2 - 1, BOARD_SIZE - 1), players[1], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(BOARD_SIZE / 2, BOARD_SIZE - 1 ), players[1], SP_DISPLAY_STR));
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
    td->init(*this);
}
// interaction commands
// ——————————————


// settors
// ——————————————
void GameBoard::setLinks(unique_ptr <vector<string>> linkPlacements, Player *player) {
    int count = (player->getPlayerName() == "Player 1") ? 0 : 8;
    int xCoord = 0;
    int yCoord = (player->getPlayerName() == "Player 1") ? 0 : 8 - 1;
    char name = (player->getPlayerName() == "Player 1") ? 'a' : 'A';

    for (auto link : *linkPlacements) {
        int strength = link[1];
        string displayName(1, name);

        if (link[0] == 'V') {
            allBoardPieces.emplace_back(make_unique<Virus>(strength, Coords(xCoord, yCoord), displayName, *player));
        } else if (link[0] == 'D') {
            allBoardPieces.emplace_back(make_unique<Data>(strength, Coords(xCoord, yCoord), displayName, *player));
        }

        if (xCoord == 2 || xCoord == 3) {
            yCoord = (player->getPlayerName() == "Player 1") ? 1 : 8 - 2;
        } else {
            yCoord = (player->getPlayerName() == "Player 1") ? 0 : 8 - 1;
        }
        xCoord++;
        name++;
        Link &ptr = *(allBoardPieces[count].get());
        td->notify(ptr);
        count++;
    }
    // TODO: create links and set in gb, handle bad input
}

void GameBoard::setAbilities(string abilities, Player *player) {
    cout << "abilities for " << player->getPlayerName() << " set" << endl;
    cout << "abilities order: " << abilities << endl;
    // TODO: create ability cards and set them in the gameboard
    // also handle bad input and throw it out maybe
    // or just deal with it lmao but maybe still cerr
}

// gettors:
// ——————————————
vector<Player>& GameBoard::getPlayers() {
    return players;
}

vector<ServerPort>& GameBoard::getServerPort() {
    return serverPorts;
}

// vector<std::shared_ptr<Link>> GameBoard::allLinks() {
//     return allBoardPieces;
// }

// TODO (FIX)-> FIGURE OUT WHAT TO RETURN
// vector<AbilityCard>& GameBoard::getAllAbilityCards() {
//     vector<AbilityCard> result;
//     for (const auto& ptr : allAbilityCards) {
//         result.push_back(*ptr); // Assuming Link has a copy constructor
//     }
//     return result;
// }

Player& GameBoard::getCurrPlayer() {
    return *currPlayer;
}

Player& GameBoard::getWinner() {
    return *winner;
}

vector<Coords>& GameBoard::getBoardBoundaries() {
    return boardBoundaries;
}

vector<EdgeCoord>& GameBoard::getEdgeCoords() {
    return edgeCoords;
}

vector<FireWall>& GameBoard::getActiveFirewalls() {
    return activeFirewalls;
}
