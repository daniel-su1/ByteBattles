#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include <memory>
#include <string>
#include "player.h"
#include "link.h"
#include "abilitycard.h"
#include "coords.h"
#include "edgecoord.h"
#include "serverport.h"
#include "abilitycards/firewall.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;
class TextDisplay; 
class GraphicsDisplay;
class GameBoard: public Subject {
    TextDisplay *td;
    GraphicsDisplay *gd;
    vector<Player> players;
    vector<shared_ptr<Link>> allLinks;
    vector<shared_ptr<AbilityCard>> allAbilityCards;

    int currPlayerIndex;
    bool currPlayerAbilityPlayed;
    int winnerIndex;
    bool isWon;

    vector<Coords> boardBoundaries;
    vector<EdgeCoord> edgeCoords;
    vector<ServerPort> serverPorts;
    vector<FireWall> activeFirewalls;
    public:
        const int PLAYER_COUNT = 2;
        const int INVALID_PLAYER = -1;
        const int ABILITY_COUNT = 5;

        const int MAX_STEPSIZE = 2;

        const int BOARD_SIZE = 8;
        const int SP_X_COORD_1 = 3;
        const int SP_X_COORD_2 = 4;
        string SP_DISPLAY_STR = "S";
        string BORDER_DISPLAY_STR = "=";

        GameBoard();
        ~GameBoard();
        friend ostream &operator<<(ostream &out, const GameBoard &gb);
        void notifyObservers() override;

        void init();
        void applyAbility(AbilityCard& ac, Player *player = nullptr); // TODO: same as movePiece for useAbility()
        void movePiece(shared_ptr<Link> link, Direction dir); // TODO: possibly move to private or delete bc of moveLink() below
        void battlePieces(Link &linkp1, Link &linkp2);
        void startNewTurn();
        void downloadIdentity(Link &link1, Player *player);
        void updateIdentity(Link& link);

        // text command interactions
        // all methods other than playerAbilities() return a string with the error message if the method fails
        void moveLink(string linkName, string direction);
        string playerAbilities(Player& player); // unlikely to fail since there is no user input
        void useAbility(int abilityID);
        void useAbility(int abilityID, string linkName); // for link boost
        void useAbility(int abilityID, int xCoord, int yCoord); // for firewall

        // setters
        void setLinks(unique_ptr <vector<string>> linkPlacements, Player *player);
        void setAbilities(string abilities, Player *player);

        // getters
        vector<Player>& getPlayers();
        unique_ptr<vector<shared_ptr<Link>>> getPlayerLinks(Player& player);
        AbilityType getAbilityType(int id);
        // vector<std::shared_ptr<Link>> getAllLinks();
        // vector<AbilityCard>& getAllAbilityCards();
        int getCurrPlayerIndex();
        int getNextPlayerIndex();
        int getWinnerIndex();
        bool getIsWon();
        vector<Coords>& getBoardBoundaries();
        vector<EdgeCoord>& getEdgeCoords();
        vector<ServerPort>& getServerPort();
        vector<FireWall>& getActiveFirewalls();
    private:
        unique_ptr<vector<shared_ptr<AbilityCard>>> getPlayerAbilities(Player& player); // possibly deletable
        shared_ptr<AbilityCard> getAbilityCard(int abilityID);
};
#endif