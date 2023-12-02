#include "gameboard.h"
#include "virus.h"
#include "data.h"
#include "abilitycards/linkboost.h"
#include "abilitycards/download.h"
#include "abilitycards/scan.h"
#include "abilitycards/polarize.h"

GameBoard::GameBoard(): td{nullptr}, players(), allBoardPieces(), allAbilityCards(),
    currPlayer{nullptr}, winner{nullptr}, boardBoundaries(), edgeCoords(),
    serverPorts(), activeFirewalls(), gd{} {}

GameBoard::~GameBoard() {
    delete td;
    delete gd;
}

ostream &operator<<(ostream &out, const GameBoard &gb) {
    cout << *gb.td << endl;
    return out;
}

void GameBoard::notifyObservers() { 
    td->notify(*this); 
    gd->notify(*this);
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

    td = new TextDisplay;
    gd = new GraphicsDisplay;
    
    // intialize players
    for (int i = 1; i <= PLAYER_COUNT; i++) {
        string playerName = "Player " + to_string(i);
        int abilityCount = ABILITY_COUNT;
        players.emplace_back(Player(playerName, abilityCount));
    }
    
    // intialize server ports; middle of board
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_1, 0), players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_2, 0), players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_1, BOARD_SIZE - 1), players[1], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_2, BOARD_SIZE - 1 ), players[1], SP_DISPLAY_STR));
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
            // non server port x coords can have winning positions at distance of 1 or 2
            // and server ports x coords can only win at distance of 1
            if (((i != SP_X_COORD_1) && (i != SP_X_COORD_2)) || stepSize == 1) { 
                // player 2's target/winning areas
                edgeCoords.emplace_back(EdgeCoord(Coords(i, 0 - stepSize), players[1], BORDER_DISPLAY_STR)); 
                // player 1's target/winning areas
                edgeCoords.emplace_back(EdgeCoord(Coords(i, BOARD_SIZE - 1 + stepSize), players[0], BORDER_DISPLAY_STR));
            }
        }
    }
    td->init(*this);
    gd->init(*this);
}
// interaction commands
// ——————————————

void GameBoard::moveLink(string linkName, string direction) {
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        throw (logic_error("i am a movelink for link boosts error message\n"));
    }
}

string GameBoard::playerAbilities(Player& player) {
    string message = player.getPlayerName() + " Abilities:\n";
    string abilities = "";
    for (int i = 0; i < allAbilityCards.size(); i++) {
        if (player.getPlayerName() == allAbilityCards[i]->getOwner().getPlayerName()) {
            string displayName = allAbilityCards[i]->getDisplayName();
            int id = allAbilityCards[i]->getAbilityId();
            string isUsed = allAbilityCards[i]->isUsed() ? "[used] ": "[avaliable] ";
            abilities += "#" + to_string(id) + "." + displayName + " " + isUsed;
        }
    }
    message += abilities;
    return (message + "\n");
}

void GameBoard::useAbility(int abilityID) {
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        throw (logic_error("i am a useability error message\n"));
    }
}

void GameBoard::useAbility(int abilityID, string linkName) { // for link boost
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        throw (logic_error("i am a useability for link boosts error message\n"));
    }
}

void GameBoard::useAbility(int abilityId, int xCoord, int yCoord) { // for firewall
    // TODO: actually implement
    bool hasError = true;
    if (hasError) {
        throw (logic_error("i am a useability for firewalls error message\n"));
    }
}

// settors
// ——————————————
void GameBoard::setLinks(unique_ptr <vector<string>> linkPlacements, Player *player) {
    bool isPlayer1 = player->getPlayerName() == "Player 1";
    int xCoord = 0;
    int yCoord = isPlayer1 ? 0 : BOARD_SIZE - 1;
    char name = isPlayer1 ? 'a' : 'A';

    for (auto link : *linkPlacements) {
        int strength = link[1];
        string displayName(1, name);

        // move yCoord towards center if blocked by server port
        if (xCoord == SP_X_COORD_1 || xCoord == SP_X_COORD_2) { 
            yCoord = isPlayer1 ? 1 : BOARD_SIZE - 2;
        } else {
            yCoord = isPlayer1 ? 0 : BOARD_SIZE - 1;
        }

        // create links and place in board
        unique_ptr<Link> curLinkPtr;
        if (link[0] == 'V') {
            Virus curLink = Virus(strength, Coords(xCoord, yCoord), displayName, *player);
            curLinkPtr = make_unique<Virus>(curLink);
            td->notify(*curLinkPtr);
            gd->notify(*curLinkPtr);
        } else if (link[0] == 'D') {
            Data curLink = Data(strength, Coords(xCoord, yCoord), displayName, *player);
            curLinkPtr = make_unique<Data>(curLink);
            td->notify(*curLinkPtr);
            gd->notify(*curLinkPtr);
        } else { // not V or D
            throw (logic_error("Error, incorrect link placements: please follow <type1><strength1> <type2><strength2> ... , where type is V or D.\n"));
        }
        allBoardPieces.emplace_back(move(curLinkPtr));

        // update position and name
        xCoord++;
        name++;
    }
    
    // not iterated towards the end
    if ((isPlayer1 && yCoord != 0) || (!isPlayer1 && yCoord != BOARD_SIZE - 1)) {
        string errorMsg = "Error, incorrect link placements: please place " + to_string(BOARD_SIZE) + " links.\n";
        throw (logic_error(errorMsg));
    }
}

void GameBoard::setAbilities(string abilities, Player *player) {
    int id = 1;

    for (char c: abilities) {
        if (c == 'L') {
            string displayName = "LinkBoost";
            allAbilityCards.emplace_back(make_unique<LinkBoost>(id, *player, displayName));
        } else if (c == 'F') {
            string displayName = "FireWall";
            allAbilityCards.emplace_back(make_unique<FireWall>(id, *player, displayName));
        } else if (c == 'D') {
            string displayName = "Download";
            allAbilityCards.emplace_back(make_unique<Download>(id, *player, displayName));
        } else if (c == 'S') {
            string displayName = "Scan";
            allAbilityCards.emplace_back(make_unique<Scan>(id, *player, displayName));
        } else if (c == 'P') {
            string displayName = "Polarize";
            allAbilityCards.emplace_back(make_unique<Polarize>(id, *player, displayName));
        } 
        if (id == 5) {
            id = 1;
        } else {
            id++;
        }
    }
    // or just deal with it lmao but maybe still cerr
}

// gettors:
// ——————————————
vector<Player>& GameBoard::getPlayers() {
    return players;
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

vector<ServerPort>& GameBoard::getServerPort() {
    return serverPorts;
}

vector<FireWall>& GameBoard::getActiveFirewalls() {
    return activeFirewalls;
}
