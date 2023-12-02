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
using namespace std;
class TextDisplay; 
class GameBoard: public Subject {
    TextDisplay *td;
    vector<Player> players;
    vector<shared_ptr<Link>> allLinks;
    vector<shared_ptr<AbilityCard>> allAbilityCards;
    int currPlayerIndex;
    int winnerIndex;
    vector<Coords> boardBoundaries;
    vector<EdgeCoord> edgeCoords;
    vector<ServerPort> serverPorts;
    vector<FireWall> activeFirewalls;
    public:
        const int PLAYER_COUNT = 2;
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
        void movePiece(Link &link, Direction dir); // TODO: possibly move to private or delete bc of moveLink() below
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
        void useAbility(int abilityId, int xCoord, int yCoord); // for firewall

        // setters
        void setLinks(unique_ptr <vector<string>> linkPlacements, Player *player);
        void setAbilities(string abilities, Player *player);

        // getters
        vector<Player>& getPlayers();
        unique_ptr<vector<shared_ptr<Link>>> getPlayerLinks(Player& player);
        // vector<std::shared_ptr<Link>> getAllLinks();
        // vector<AbilityCard>& getAllAbilityCards();
        int getCurrPlayerIndex();
        int getNextPlayerIndex();
        int getWinnerIndex();
        vector<Coords>& getBoardBoundaries();
        vector<EdgeCoord>& getEdgeCoords();
        vector<ServerPort>& getServerPort();
        vector<FireWall>& getActiveFirewalls();
    private: // oops possibly deletable
        unique_ptr<vector<shared_ptr<AbilityCard>>> getPlayerAbilities(Player& player);
};
#endif