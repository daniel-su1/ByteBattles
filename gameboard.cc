#include <map>
#include "gameboard.h"
#include "abilitycards/backup.h"
#include "abilitycards/download.h"
#include "abilitycards/movetwice.h"
#include "abilitycards/linkboost.h"
#include "abilitycards/polarize.h"
#include "abilitycards/scan.h"
#include "abilitycards/wall.h"
#include "data.h"
#include "virus.h"

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

GameBoard::~GameBoard() {}

ostream& operator<<(ostream& out, const GameBoard& gb) {
    cout << *gb.td;
    return out;
}

// update both players' info
void GameBoard::notifyObservers() {
    td->notify(*this);
    if (graphicsEnabled) gd->notify(*this);
}

// player info has updated
void GameBoard::notifyObservers(Player& player) {
    if (graphicsEnabled) gd->notify(player);
}

// link position has moved
void GameBoard::notifyObservers(Link& link) {
    td->notify(link);
    if (graphicsEnabled) gd->notify(link);
}

// draw firewall
void GameBoard::notifyObservers(FireWall firewall) {
    td->notify(firewall);
    if (graphicsEnabled) gd->notify(firewall);
}

// draw wall
void GameBoard::notifyObservers(Wall wall) {
    td->notify(wall);
    if (graphicsEnabled) gd->notify(wall);
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
    activeWalls.clear();
    
    td = new TextDisplay;

    // intialize players
    for (int i = 1; i <= PLAYER_COUNT; i++) {
        string playerName = "Player " + to_string(i);
        int abilityCount = ABILITY_COUNT;
        players.emplace_back(make_shared<Player>(playerName, abilityCount));
    }

    // intialize server ports; middle of board
    serverPorts.emplace_back(
        ServerPort(Coords(SP_X_COORD_1, 0), *players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(
        ServerPort(Coords(SP_X_COORD_2, 0), *players[0], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_1, BOARD_SIZE - 1),
                                        *players[1], SP_DISPLAY_STR));
    serverPorts.emplace_back(ServerPort(Coords(SP_X_COORD_2, BOARD_SIZE - 1),
                                        *players[1], SP_DISPLAY_STR));

    // adding board boundaries based on board sizes
    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            boardBoundaries.emplace_back(Coords(0 - stepSize, i));
            boardBoundaries.emplace_back(Coords(BOARD_SIZE - 1 + stepSize, i));
        }
    }

    for (int stepSize = 1; stepSize <= MAX_STEPSIZE; stepSize++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            // non server port x coords can have winning positions at distance
            // of 1 or 2 and server ports x coords can only win at distance of 1
            if (((i != SP_X_COORD_1) && (i != SP_X_COORD_2)) || stepSize == 1) {
                // player 2's target/winning areas
                edgeCoords.emplace_back(EdgeCoord(
                    Coords(i, 0 - stepSize), *players[1], BORDER_DISPLAY_STR));
                // player 1's target/winning areas
                edgeCoords.emplace_back(
                    EdgeCoord(Coords(i, BOARD_SIZE - 1 + stepSize), *players[0],
                              BORDER_DISPLAY_STR));
            }
        }
    }
    td->init(*this);
}

void GameBoard::movePiece(Link& link, Direction dir) {
    // set coords
    link.movePiece(dir);
    // update view
    notifyObservers(link);
}

void GameBoard::redrawPlayerInfo(int index){
    if(graphicsEnabled){
        gd->renderPlayerInfo(*players.at(index).get());
        gd->redrawBoard(*players.at(index).get());
    }
}

// player downloads link1 (becomes the new owner)
void GameBoard::downloadLink(Link& link1, Player* player) {
    if (player == nullptr) { // called from download's activate function
        player = &(*players[currPlayerIndex]);
    }
    cout << player->getPlayerName() << " has downloaded "
         << link1.getDisplayName() << ":" << endl;
    revealIdentity(link1);
    link1.setDownloaded(true);
    link1.downloadLink();
    link1.attachDownloader(player);
    if (link1.getType() == LinkType::DATA) {
        player->setNumDataDownloaded(player->getNumDataDownloads() + 1);
    } else { // must be virus
        player->setNumVirusDownloaded(player->getNumVirusDownloads() + 1);
    }
    if (player->getNumDataDownloads() == 4) {
        player->setIsWon(true);
    } 
    if (player->getNumVirusDownloads() == 4) {
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i]->getPlayerName() != player->getPlayerName()) {
                players[i]->setIsWon(true);
            }
        }
    }

    // notifyObservers(link1);
}

void GameBoard::battlePieces(Link& link1, Link& link2) {
    cout << "BATTLE:" << endl;
    cout << "——————" << endl;
    cout << "Initiated by: " << link1.getDisplayName() << endl;
    cout << "Link " << link1.getDisplayName()
         << " Strength:" << link1.getStrength() << endl;
    cout << "Link " << link2.getDisplayName()
         << " Strength:" << link2.getStrength() << endl;
    if (link2.getStrength() > link1.getStrength()) {
        downloadLink(link1, &(link2.getOwner()));
        link2.setIdentityRevealed(true);
    } else {
        downloadLink(link2, &(link1.getOwner()));
        link1.setIdentityRevealed(true);
    }
}

void GameBoard::revealIdentity(Link& link, bool toggleLink) {
    string linkType = (link.getType() == LinkType::VIRUS) ? "Virus" : "Data";
    string out = link.getDisplayName() + " is a " + linkType + " of strength " + to_string(link.getStrength()) + ".";
    // update link
    if (toggleLink) link.setIdentityRevealed(true);
    // update view
    notifyObservers(link.getOwner());
    // print reveal
    cout << out << endl;
}

// interaction commands
// ——————————————

void GameBoard::moveLink(string linkName, string direction) {
    Direction dir;
    Player& currPlayer = *players[getCurrPlayerIndex()];
    Player& nextPlayer = *players[getNextPlayerIndex()];

    // find the link with name linkName owned by current player
    vector<shared_ptr<Link>> playerLinks = *(getPlayerLinks(currPlayer));
    try {
        Link& l = *findLink(linkName, playerLinks);
    

        // set new coords
        int newX = l.getCurrCoords().getX();
        int newY = l.getCurrCoords().getY();
        int stepSize = l.getStepSize();
        if (direction == "up") {
            dir = Direction::Up;
            newY = l.getCurrCoords().getY() - stepSize;
        } else if (direction == "down") {
            dir = Direction::Down;
            newY = l.getCurrCoords().getY() + stepSize;
        } else if (direction == "right") {
            dir = Direction::Right;
            newX = l.getCurrCoords().getX() + stepSize;
        } else if (direction == "left") {
            dir = Direction::Left;
            newX = l.getCurrCoords().getX() - stepSize;
        } else {
            throw(logic_error("Error: Not a valid move direction!\n"));
        }

        // ———————— checking move legality ——————— //
        Coords newCoord{newX, newY};

        // checking if moved off edge
        for (size_t i = 0; i < boardBoundaries.size(); i++) {
            if (newCoord == boardBoundaries[i]) {
                throw(
                    logic_error("Error: Illegal Move - you cannot move your piece "
                                "off this edge!\n"));
            }
        }

        // checking if moved into winning edge pieces
        for (size_t i = 0; i < edgeCoords.size(); i++) {
            Coords edgeCoord = edgeCoords[i].getCoords();
            if (newCoord == edgeCoord) {
                if (nextPlayer.getPlayerName() !=
                    edgeCoords[i].getOwner().getPlayerName()) {
                    downloadLink(l, &currPlayer);
                    notifyObservers(currPlayer);
                    return;
                } else {
                    throw(
                        logic_error("Error: Illegal Move - you cannot move your "
                                    "piece off this edge!\n"));
                }
            }
        }

        // check if moved onto firewall
        for (size_t i = 0; i < activeFirewalls.size(); i++) {
            FireWall currFireWall = activeFirewalls[i];
            Coords fireWallCoords = currFireWall.getCoords();
            if (newCoord == fireWallCoords) {
                if (&currFireWall.getOwner() != &l.getOwner()) {
                    // if firewall isn't owned by the link's owner, reveal the link
                    // and download if virus
                    cout << "Firewall passed!" << endl;
                    if (l.getType() == LinkType::VIRUS) {
                        downloadLink(l, &(*players[currPlayerIndex]));
                    } else {
                        cout << "Identity revealed for " << l.getDisplayName() << ":" << endl;
                        revealIdentity(l);
                    }
                }
            }
        }

        // walls
        for (size_t i = 0; i < activeWalls.size(); i++) {
            Wall currWall = activeWalls[i];
            Coords wallCoords = currWall.getCoords();
            if (newCoord == wallCoords) {
                    throw(
                        logic_error("Error: Illegal Move - Cannot move onto a wall\n"));
            }
        }

        // checking if moved on top of another piece
        for (size_t i = 0; i < allLinks.size(); i++) {
            Coords pieceCoords = allLinks[i]->getCurrCoords();
            if (newCoord == pieceCoords) {
                if (&allLinks[i]->getOwner() == &l.getOwner()) {
                    throw(
                        logic_error("Error: Illegal Move — one of your pieces "
                                    "occupies this space!\n"));
                } else {
                    battlePieces(l, *allLinks[i]);
                    movePiece(l, dir);
                    endTurn();
                    return;
                }
            }
        }

        // checking if moved onto one's own server ports / into opponents
        for (size_t i = 0; i < serverPorts.size(); i++) {
            Coords serverPortCoord = serverPorts[i].getCoords();
            if (newCoord == serverPortCoord) {
                if (&(serverPorts[i].getOwner()) == &l.getOwner()) {
                    throw(
                        logic_error("Error: Illegal Move - cannot move piece onto "
                                    "your own server port\n"));
                } else {  // other player downloads link
                    downloadLink(l, &currPlayer);
                    endTurn();
                    return;
                }
            }
        }

        movePiece(l, dir);
        endTurn();

    } catch (logic_error& e) {
        throw;
    }
}

string GameBoard::playerAbilities(Player& player) {
    string message = player.getPlayerName() + " Abilities:\n";
    string abilitiesStr = "";
    vector<shared_ptr<AbilityCard>> abilities = *getPlayerAbilities(player);
    for (shared_ptr<AbilityCard> ability : abilities) {
        string displayName = ability->getDisplayName();
        int id = ability->getAbilityId();
        string isUsed = ability->isUsed() ? "[used] " : "[avaliable] ";
        abilitiesStr += "#" + to_string(id) + "." + displayName + " " + isUsed;
    }
    message += abilitiesStr;
    return (message + "\n");
}

// movetwice
void GameBoard::useAbility(int abilityId) {
    shared_ptr<AbilityCard> ac = getAbilityCard(abilityId);
    ac->activate();
    cout << "Ability #" << to_string(abilityId) << ". " << ac->getDisplayName();
    cout << "was used." << endl;
}

// for firewall, wall
void GameBoard::useAbility(int abilityID, int xCoord, int yCoord) {
    // max one ability per turn
    if (currPlayerAbilityPlayed) {
        throw(
            logic_error("Error: an ability has already been used this turn. "
                        "Please move a link to proceed."));
    }

    shared_ptr<AbilityCard> ac = getAbilityCard(abilityID);
    
    // ability already used
    if (ac->isUsed()) {
        throw (logic_error("Error: ability has already been used."));
    }

    ac->activate(xCoord, yCoord);
    cout << "Ability #" << to_string(abilityID) << ". " << ac->getDisplayName();
    cout << " was used at (" << to_string(xCoord) << "," << to_string(yCoord)
         << ")." << endl;
    if (graphicsEnabled) {
        //gd->redrawBoard(ac.get()->getOwner());
        gd->renderPlayerInfo(ac.get()->getOwner());
    }
    currPlayerAbilityPlayed = true;
}

void GameBoard::drawAbilities(){
    gd->renderAbilityCards(*players.at(getCurrPlayerIndex()));
}

// for remaining abilities
void GameBoard::useAbility(int abilityID, string linkName) {
    try {
        // max one ability per turn
        if (currPlayerAbilityPlayed) {
            throw(
                logic_error("Error: an ability has already been used this turn. "
                            "Please move a link to proceed."));
        }

        shared_ptr<AbilityCard> ac = getAbilityCard(abilityID);

        // ability already used
        if (ac->isUsed()) {
            throw (logic_error("Error: ability has already been used."));
        }
        
        // check link type:
        // link boost must be applied to a link that is owned by currPlayer
        // download must be applied to an opponent's link
        vector<shared_ptr<Link>> links = allLinks;
        shared_ptr<Link> link;
        AbilityType type = getAbilityType(abilityID);
        switch (type) {
            case AbilityType::LINKBOOST: {
                link = findLink(linkName, *getPlayerLinks(*players[currPlayerIndex]));
                break;
            }
            case AbilityType::DOWNLOAD: {
                link = findLink(linkName, *getPlayerLinks(*players[getNextPlayerIndex()]));
                break;
            }
            case AbilityType::POLARIZE: {
                // polarize can be used on all links
                link = findLink(linkName, allLinks, false);
                break;
            }
            default: {
                link = findLink(linkName, allLinks);
                break;
            }
        }

        ac->activate(*link);
        cout << "Ability #" << to_string(abilityID) << ". " << ac->getDisplayName();
        cout << " was used on Link " << linkName << "." << endl;

        currPlayerAbilityPlayed = true;
    } catch (logic_error& e) {
        throw;
    }
    //if ((getAbilityType(abilityID) == AbilityType::DOWNLOAD ||  (getAbilityType(abilityID) == AbilityType::SCAN) )&& graphicsEnabled){
     //   gd->notify(*players[getNextPlayerIndex()]);
   // }
}

// setters
// ——————————————
void GameBoard::setGraphicsDisplay(GraphicsDisplay* gd) {
    this->gd = gd;
    graphicsEnabled = true;
    gd->init(*this);
}

void GameBoard::setLinks(unique_ptr<vector<string>> linkPlacements,
                         shared_ptr<Player> player) {
    bool isPlayer1 = player->getPlayerName() == P1_NAME;
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
        if (link[0] == VIRUS_DISPLAY_STR[0]) {
            string typeAndStrength = VIRUS_DISPLAY_STR + to_string(strength);
            Virus curLink = Virus(strength, Coords(xCoord, yCoord), displayName,
                                  *player, typeAndStrength);
            curLinkPtr = make_shared<Virus>(curLink);
            notifyObservers(*curLinkPtr);
        } else if (link[0] == DATA_DISPLAY_STR[0]) {
            string typeAndStrength = DATA_DISPLAY_STR + to_string(strength);
            Data curLink = Data(strength, Coords(xCoord, yCoord), displayName,
                                *player, typeAndStrength);
            curLinkPtr = make_shared<Data>(curLink);
            notifyObservers(*curLinkPtr);
        } else {  // not V or D
            throw(
                logic_error("Error, incorrect link placements: please follow "
                            "<type1><strength1> <type2><strength2> ... , where "
                            "type is V or D.\n"));
        }
        allLinks.emplace_back(move(curLinkPtr));

        // update position and name
        xCoord++;
        name++;

        player->setLinksSet(true);
    }

    // not iterated towards the end
    if ((isPlayer1 && yCoord != 0) ||
        (!isPlayer1 && yCoord != BOARD_SIZE - 1)) {
        string errorMsg = "Error, incorrect link placements: please place " +
                          to_string(BOARD_SIZE) + " links.\n";
        throw(logic_error(errorMsg));
    }
}

void GameBoard::enableBonus(){
    bonusEnabled = true;
}

void GameBoard::enableMoveTwice() {
    canMoveTwice = true;
}

void GameBoard::setAbilities(string abilities, shared_ptr<Player> player) {
    int id = 1;
    map <char, int> abilitiesCount;

    for (char c : abilities) {
        if (c == 'L') {
            string displayName = "LinkBoost";
            allAbilityCards.emplace_back(
                make_shared<LinkBoost>(id, *player, displayName));
        } else if (c == 'F') {
            string displayName = "FireWall";
            allAbilityCards.emplace_back(
                make_shared<FireWall>(id, *player, displayName, this));
        } else if (c == 'D') {
            string displayName = "Download";
            allAbilityCards.emplace_back(
                make_shared<Download>(id, *player, displayName, this));
        } else if (c == 'P') {
            string displayName = "Polarize";
            allAbilityCards.emplace_back(
                make_shared<Polarize>(id, *player, displayName, this));
        } else if (c == 'S') {
            string displayName = "Scan";
            allAbilityCards.emplace_back(
                make_shared<Scan>(id, *player, displayName, this));
        } else if (c == 'W') {
            string displayName = "Wall";
            allAbilityCards.emplace_back(
                make_shared<Wall>(id, *player, displayName, this));
        } else if (c == 'B') {
            string displayName = "BackUp";
            allAbilityCards.emplace_back(
                make_shared<BackUp>(id, *player, displayName, this));
        } else if (c == 'M') {
            string displayName = "MoveTwice";
            allAbilityCards.emplace_back(
                make_shared<MoveTwice>(id, *player, displayName, this));
        } else {
            string errorMsg = "Incorrect ability type: please use one of:\n";
            errorMsg +=
                "\tL (LinkBoost)\n\tF (FireWall)\n\tD (Download)\n\tP "
                "(Polarize)\n";
            errorMsg += "\tS (Scan)\n\tW (Wall)\n\tB (BackUp)\n\tM (MoveTwice)";
            throw(logic_error(errorMsg));
        }
        id++;
        abilitiesCount[c]++;
        if (abilitiesCount[c] > 2) {
            throw (logic_error("Error: maximum 2 abilities per type."));
        }
    }
    if (id != ABILITY_COUNT + 1) {
        throw(logic_error("Error: please give " + to_string(ABILITY_COUNT) +
                          " abilities."));
    }
    player->setAbilitiesSet(true);
}

void GameBoard::checkSquareOccupancy(int x, int y) {
    for (auto i : allLinks) {
        if (i->getCurrCoords().getX() == x && i->getCurrCoords().getY() == y) {
            throw std::logic_error("Error: please place on empty square");
        }
    }
    for (auto i : getActiveFirewalls()) {
        if (i.getCoords().getX() == x && i.getCoords().getY() == y) {
            throw std::logic_error("Error: please place on empty square");
        }
    }
    for (auto i : getActiveWalls()) {
        if (i.getCoords().getX() == x && i.getCoords().getY() == y) {
            throw std::logic_error("Error: please place on empty square");
        }
    }
    for (auto i : getServerPort()) {
        if (i.getCoords().getX() == x && i.getCoords().getY() == y) {
            throw std::logic_error("Error: please place on empty square");
        }
    }
}

void GameBoard::addFireWall(FireWall firewall) {
    checkSquareOccupancy(firewall.getCoords().getX(),
                         firewall.getCoords().getY());
    activeFirewalls.emplace_back(firewall);
    notifyObservers(firewall);
}

void GameBoard::addWall(Wall wall) {
    checkSquareOccupancy(wall.getCoords().getX(),
                         wall.getCoords().getY());
    activeWalls.emplace_back(wall);
    notifyObservers(wall);
}

// getters:
// ——————————————
vector<shared_ptr<Player>>& GameBoard::getPlayers() { return players; }

unique_ptr<vector<shared_ptr<AbilityCard>>> GameBoard::getPlayerAbilities(
    Player& player) {
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

bool GameBoard::getGraphicsEnabled() {return graphicsEnabled;}

int GameBoard::getCurrPlayerIndex() { return currPlayerIndex; }

int GameBoard::getNextPlayerIndex() { return currPlayerIndex ? 0 : 1; }

int GameBoard::getWinnerIndex() { return winnerIndex; }

bool GameBoard::getIsWon() { return isWon; }

vector<Coords>& GameBoard::getBoardBoundaries() { return boardBoundaries; }

vector<EdgeCoord>& GameBoard::getEdgeCoords() { return edgeCoords; }

vector<ServerPort>& GameBoard::getServerPort() { return serverPorts; }

vector<FireWall>& GameBoard::getActiveFirewalls() { return activeFirewalls; }

vector<Wall>& GameBoard::getActiveWalls() { return activeWalls; }

shared_ptr<AbilityCard> GameBoard::getAbilityCard(int abilityID) {
    shared_ptr<Player> currPlayer = players[currPlayerIndex];
    vector<shared_ptr<AbilityCard>> cards = *getPlayerAbilities(*currPlayer);
    for (shared_ptr<AbilityCard> ac : cards) {
        if (ac->getAbilityId() == abilityID) {
            return ac;
        }
    }
    string errorMsg = "Error, unable to find ability card with id " +
                      to_string(abilityID) + " owned by " +
                      currPlayer->getPlayerName() +
                      ".\nSee all abilities with the \"abilities\" command.";
    throw(logic_error(errorMsg));
}

shared_ptr<Link> GameBoard::findLink(string linkName,
                                     vector<shared_ptr<Link>> links,
                                     bool checkDownloaded) {
    for (shared_ptr<Link> link : links) {
        if (linkName == link->getDisplayName()) {
            if (checkDownloaded && link->isDownloaded()) {
                throw (logic_error("This piece has already been downloaded!"));
            }
            return link;
        }
    }
    throw(logic_error("Error: Link not found"));
}

void GameBoard::startNewTurn() {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i]->isWon()) {
            isWon = true;
        }
    }
    currPlayerIndex = getNextPlayerIndex();
    currPlayerAbilityPlayed = false;
    notifyObservers();
}

void GameBoard::endTurn() {
    //notifyObservers();
    if (canMoveTwice) {
        canMoveTwice = false;
    } else {
        startNewTurn();
    }
}
