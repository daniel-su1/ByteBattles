#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <memory>
#include <string>
#include <vector>

#include "abilitycard.h"
#include "abilitycards/firewall.h"
#include "coords.h"
#include "edgecoord.h"
#include "graphicsdisplay.h"
#include "link.h"
#include "player.h"
#include "serverport.h"
#include "textdisplay.h"
#include "window.h"

using namespace std;

class TextDisplay;
class GraphicsDisplay;

class GameBoard : public Subject {
    TextDisplay* td;
    GraphicsDisplay* gd;
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Link>> allLinks;
    vector<shared_ptr<AbilityCard>> allAbilityCards;

    int currPlayerIndex;
    bool currPlayerAbilityPlayed;
    int winnerIndex;
    bool isWon;
    bool graphicsEnabled;
    bool bonusEnabled;

    vector<Coords> boardBoundaries;
    vector<EdgeCoord> edgeCoords;
    vector<ServerPort> serverPorts;
    vector<FireWall> activeFirewalls;

   public:
    const int PLAYER_COUNT = 2;
    const string P1_NAME = "Player 1";
    const string P2_NAME = "Player 2";
    const int INVALID_PLAYER = -1;
    const int ABILITY_COUNT = 5;

    const int MAX_STEPSIZE = 2;

    const int BOARD_SIZE = 8;
    const int SP_X_COORD_1 = 3;
    const int SP_X_COORD_2 = 4;

    const string SP_DISPLAY_STR = "S";
    const string DATA_DISPLAY_STR = "D";
    const string VIRUS_DISPLAY_STR = "V";
    const string FIREWALL_P1_STR = "m";
    const string FIREWALL_P2_STR = "w";

    const string BORDER_DISPLAY_STR = "=";

    GameBoard();
    ~GameBoard();
    friend ostream& operator<<(ostream& out, const GameBoard& gb);
    void notifyObservers() override;
    void notifyObservers(FireWall firewall);

    void init();
    void battlePieces(Link& linkp1, Link& linkp2);
    void startNewTurn();
    void downloadLink(Link& link1, Player *player = nullptr);
    void updateIdentity(Link& link);
    void revealIdentity(Link& link);

    // text command interactions
    void moveLink(string linkName, string direction);
    string playerAbilities(Player& player);
    void useAbility(int abilityId, int xCoord,
                    int yCoord);  // for firewall and wall
    void useAbility(int abilityID, string linkName = "");  // for remaining abilities
    // default to empty for skip turn ability

    // setters
    void setLinks(unique_ptr<vector<string>> linkPlacements,
                  shared_ptr<Player> player);
    void setAbilities(string abilities, shared_ptr<Player> player);
    void enableBonus();
    void setGraphicsDisplay(GraphicsDisplay* gd);
    void addFireWall(FireWall firewall);
    // getters
    vector<shared_ptr<Player>>& getPlayers();
    unique_ptr<vector<shared_ptr<Link>>> getPlayerLinks(Player& player);
    AbilityType getAbilityType(int id);
    int getCurrPlayerIndex();
    int getNextPlayerIndex();
    int getWinnerIndex();
    bool getIsWon();
    vector<Coords>& getBoardBoundaries();
    vector<EdgeCoord>& getEdgeCoords();
    vector<ServerPort>& getServerPort();
    vector<FireWall>& getActiveFirewalls();
    void enableGraphics();
    bool getGraphicsEnabled();
    void drawAbilities();
    void redrawPlayerInfo(int index);
   private:
    void movePiece(Link& link, Direction dir);
    unique_ptr<vector<shared_ptr<AbilityCard>>> getPlayerAbilities(Player& player);
    shared_ptr<AbilityCard> getAbilityCard(int abilityID);
    void checkSquareOccupancy(int x, int y);
    shared_ptr<Link> findLink(string linkName, vector<shared_ptr<Link>> links);
};
#endif
