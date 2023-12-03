#include "gameboard.h"
#include "virus.h"
#include "data.h"
#include "abilitycards/linkboost.h"
#include "abilitycards/download.h"
#include "abilitycards/scan.h"
#include "abilitycards/polarize.h"

GameBoard::GameBoard()
    : td(nullptr),
      gd(nullptr),
      players(),
      allLinks(),
      allAbilityCards(),
      currPlayerIndex(INVALID_PLAYER),
      currPlayerAbilityPlayed(false),
      winnerIndex(INVALID_PLAYER),
      isWon(false),
      graphicsEnabled(false),
      boardBoundaries(),
      edgeCoords(),
      serverPorts(),
      activeFirewalls() {}

GameBoard::~GameBoard() {
    delete td;
    delete gd;
}


ostream &operator<<(ostream &out, const GameBoard &gb) {
    cout << *gb.td;
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
    allLinks.clear();
    allAbilityCards.clear();
    currPlayerIndex = 0;
    winnerIndex = -1;
    boardBoundaries.clear();
    edgeCoords.clear();
    serverPorts.clear();
    activeFirewalls.clear();
    observers.clear();

    td = new TextDisplay;
    gd = new GraphicsDisplay;
    observers = std::vector<Observer*>();
    
    // intialize players
    for (int i = 1; i <= PLAYER_COUNT; i++) {
        string playerName = "Player " + to_string(i);
        int abilityCount = ABILITY_COUNT;
        players.emplace_back(make_shared<Player>(playerName, abilityCount));
    }
    
    // intialize server ports; middle of board
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_1, 0), *players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_2, 0), *players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_1, BOARD_SIZE - 1), *players[1], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_2, BOARD_SIZE - 1 ), *players[1], SP_DISPLAY_STR));

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
                edgeCoords.emplace_back(EdgeCoord(Coords(i, 0 - stepSize), *players[1], BORDER_DISPLAY_STR)); 
                // player 1's target/winning areas
                edgeCoords.emplace_back(EdgeCoord(Coords(i, BOARD_SIZE - 1 + stepSize), *players[0], BORDER_DISPLAY_STR));
            }
        }
    }
    td->init(*this);
    gd->init(*this);
}

void GameBoard::movePiece(shared_ptr<Link> link, Direction dir) {
    link->movePiece(dir);
    td->notify(*link);
    gd->notify(*link);
}

// player downloads link1 (becomes the new owner)
void GameBoard::downloadIdentity(shared_ptr<Link> link1, Player *player) {
    cout << player->getPlayerName() << " has downloaded " << link1->getDisplayName() << ":" <<  endl;
    string linkType = (link1->getType() == LinkType::virus) ? "Virus" : "Data";
    cout << "A " << linkType << " of strength " << link1->getStrength() << "." << endl;
    link1->setDownloaded(true); 
    link1->downloadLink();
    if (linkType == "Data") {
        player->setNumDataDownloaded(player->getNumDataDownloads() + 1);
    } else if (linkType == "Virus") {
        player->setNumVirusDownloaded(player->getNumVirusDownloads() + 1);
    }
    td->notify(*link1);
    gd->notify(*link1);

}

void GameBoard::startNewTurn() {
    if (winnerIndex != INVALID_PLAYER) {
        isWon = true; // where do we check this lol TODO: check if christina did this already
    }
    currPlayerIndex = getNextPlayerIndex();
    currPlayerAbilityPlayed = false;
}

// interaction commands
// ——————————————

void GameBoard::moveLink(string linkName, string direction) {
    shared_ptr<Link> l;
    Direction dir = Direction::Up;
    bool notFound = true;
    Player& p = *players[currPlayerIndex];

    // find the link with name linkName owned by current player
    vector<shared_ptr<Link>> playerLinks = *(getPlayerLinks(p));
    for (shared_ptr<Link> link : playerLinks) {
        if (linkName == link->getDisplayName()) {
            l = link;
            notFound = false;
        }
    }

    if (notFound) {
        string errorMsg = "Error: " + linkName + " is not owned by " + p.getPlayerName() + ".\n";
        throw(logic_error(errorMsg));
    }

    int newX = l->getCurrCoords().getX();
    int newY = l->getCurrCoords().getY();
    int stepSize = l->getStepSize();
    if (direction == "up") {
        dir =  Direction::Up;
        newY = l->getCurrCoords().getY() - stepSize;
    } else if (direction == "down") {
        dir = Direction::Down;
        newY = l->getCurrCoords().getY() + stepSize;
    } else if (direction == "right") {
        dir = Direction::Right;
        newX = l->getCurrCoords().getX() + stepSize;
    } else if (direction == "left") {
        dir = Direction::Left;
        newX = l->getCurrCoords().getX() - stepSize;
    } else {
        throw(logic_error("Error: Not a valid move direction!\n"));
    }
    //———————— checking move legality ——————— //
    Coords newCoord{newX, newY};

    // checking if moved off edge
    for (size_t i = 0; i < boardBoundaries.size(); i++) {
        if (newCoord == boardBoundaries[i]) {
            throw(logic_error("Error: Illegal Move - you cannot move your piece off this edge!\n"));
        }
    }

    // checking if moved on top of own piece
    for (size_t i = 0; i < allLinks.size(); i++) {
        Coords pieceCoords = allLinks[i]->getCurrCoords();
        if (newCoord == pieceCoords) {
            if (&allLinks[i]->getOwner() == &l->getOwner()) {
                throw(logic_error("Error: Illegal Move — one of your pieces occupies this space!\n"));
            } else {
                // do battle
            }
        }
    }
    // checking if moved onto one's own server ports / into opponents 
    for (size_t i = 0; i < serverPorts.size(); i++) {
        Coords serverPortCoord = serverPorts[i].getCoords();
        if (newCoord == serverPortCoord) {
            if (&(serverPorts[i].getOwner()) == &l->getOwner()) {
                throw(logic_error("Error: Illegal Move - cannot move piece onto your own server port\n"));
            } else { // other player downloads link
                Player originalOwner = l->getOwner();
                Player& newOwner = *players[getNextPlayerIndex()];
                downloadIdentity(l, &newOwner);
                startNewTurn();
                gd->notify(*this);
                return;
            }
        }
    }
    
    movePiece(l, dir);
    startNewTurn();
}

string GameBoard::playerAbilities(Player& player) {
    string message = player.getPlayerName() + " Abilities:\n";
    string abilitiesStr = "";
    vector<shared_ptr<AbilityCard>> abilities = *getPlayerAbilities(player);
    for (shared_ptr<AbilityCard> ability : abilities) {
        string displayName = ability->getDisplayName();
        int id = ability->getAbilityId();
        string isUsed = ability->isUsed() ? "[used] ": "[avaliable] ";
        abilitiesStr += "#" + to_string(id) + "." + displayName + " " + isUsed;
    }
    message += abilitiesStr;
    return (message + "\n");
}

void GameBoard::useAbility(int abilityID) {
    // max one ability per turn
    if (currPlayerAbilityPlayed) {
        throw (logic_error("Error: an ability has already been used this turn. Please move a link to proceed."));
    }
    currPlayerAbilityPlayed = true;

    shared_ptr<AbilityCard> ac = getAbilityCard(abilityID);
    ac->activate();
}

// for link boost
void GameBoard::useAbility(int abilityID, string linkName) {
    // max one ability per turn
    if (currPlayerAbilityPlayed) {
        throw (logic_error("Error: an ability has already been used this turn. Please move a link to proceed."));
    }
    currPlayerAbilityPlayed = true;

    shared_ptr<AbilityCard> ac = getAbilityCard(abilityID);
    ac->activate();
}

// for firewall
void GameBoard::useAbility(int abilityID, int xCoord, int yCoord) {
    // max one ability per turn
    if (currPlayerAbilityPlayed) {
        throw (logic_error("Error: an ability has already been used this turn. Please move a link to proceed."));
    }
    currPlayerAbilityPlayed = true;

    shared_ptr<AbilityCard> ac = getAbilityCard(abilityID);
    ac->activate();
}

// setters
// ——————————————
void GameBoard::setLinks(unique_ptr <vector<string>> linkPlacements, shared_ptr<Player> player) {
    bool isPlayer1 = player->getPlayerName() == "Player 1";
    int xCoord = 0;
    int yCoord = isPlayer1 ? 0 : BOARD_SIZE - 1;
    char name = isPlayer1 ? 'a' : 'A';

    for (auto link : *linkPlacements) {
        int strength = link[1] - '0';
        string displayName(1, name);

        // move yCoord towards center if blocked by server port
        if (xCoord == SP_X_COORD_1 || xCoord == SP_X_COORD_2) { 
            yCoord = isPlayer1 ? 1 : BOARD_SIZE - 2;
        } else {
            yCoord = isPlayer1 ? 0 : BOARD_SIZE - 1;
        }

        // create links and place in board
        shared_ptr<Link> curLinkPtr;
        if (link[0] == 'V') {
            Virus curLink = Virus(strength, Coords(xCoord, yCoord), displayName, *player);
            curLinkPtr = make_shared<Virus>(curLink);
            td->notify(*curLinkPtr);
            gd->notify(*curLinkPtr);
        } else if (link[0] == 'D') {
            Data curLink = Data(strength, Coords(xCoord, yCoord), displayName, *player);
            curLinkPtr = make_shared<Data>(curLink);
            td->notify(*curLinkPtr);
            gd->notify(*curLinkPtr);
        } else { // not V or D
            throw (logic_error("Error, incorrect link placements: please follow <type1><strength1> <type2><strength2> ... , where type is V or D.\n"));
        }
        allLinks.emplace_back(move(curLinkPtr));

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

void GameBoard::setAbilities(string abilities, shared_ptr<Player> player) {
    int id = 1;

    for (char c: abilities) {
        if (c == 'L') {
            string displayName = "LinkBoost";
            allAbilityCards.emplace_back(make_shared<LinkBoost>(id, *player, displayName));
        } else if (c == 'F') {
            string displayName = "FireWall";
            allAbilityCards.emplace_back(make_shared<FireWall>(id, *player, displayName));
        } else if (c == 'D') {
            string displayName = "Download";
            allAbilityCards.emplace_back(make_shared<Download>(id, *player, displayName));
        } else if (c == 'S') {
            string displayName = "Scan";
            allAbilityCards.emplace_back(make_shared<Scan>(id, *player, displayName));
        } else if (c == 'P') {
            string displayName = "Polarize";
            allAbilityCards.emplace_back(make_shared<Polarize>(id, *player, displayName));
        } 
        if (id == 5) {
            id = 1;
        } else {
            id++;
        }
    }
    // or just deal with it lmao but maybe still cerr
}

// getters:
// ——————————————
vector<shared_ptr<Player>>& GameBoard::getPlayers() {
    return players;
}

unique_ptr<vector<shared_ptr<AbilityCard>>> GameBoard::getPlayerAbilities(Player& player) {
    vector<shared_ptr<AbilityCard>> result;
    for (shared_ptr<AbilityCard> ac : allAbilityCards) {
        if (player.getPlayerName() == ac->getOwner().getPlayerName()) {
            result.emplace_back(ac);
        }
    }
    return make_unique<vector<shared_ptr<AbilityCard>>>(result);
}

unique_ptr<vector<shared_ptr<Link>>> GameBoard::getPlayerLinks(Player& player) {
    vector<shared_ptr<Link>> result;
    for (shared_ptr<Link> link : allLinks) {
        if (player.getPlayerName() == link->getOwner().getPlayerName()) {
            result.emplace_back(link);
        }
    }
    return make_unique<vector<shared_ptr<Link>>>(result);
}

AbilityType GameBoard::getAbilityType(int id) {
    shared_ptr<AbilityCard> ac = getAbilityCard(id);
    return ac->getType();
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

int GameBoard::getCurrPlayerIndex() {
    return currPlayerIndex;
}

int GameBoard::getNextPlayerIndex() {
    return currPlayerIndex ? 0 : 1;
}

int GameBoard::getWinnerIndex() {
    return winnerIndex;
}

bool GameBoard::getIsWon() {
    return isWon;
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

shared_ptr<AbilityCard> GameBoard::getAbilityCard(int abilityID) {
    for (shared_ptr<AbilityCard> ac : allAbilityCards) {
        if (ac->getAbilityId() == abilityID) {
            return ac;
        }
    }
    string errorMsg = "Error, unable to find ability card with id " + to_string(abilityID) + ". See all abilities with the \"abilities\" command.";
    throw (logic_error(errorMsg));
}
