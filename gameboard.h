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
#include "window.h"

using namespace std;
class TextDisplay; 
class GraphicsDisplay;
class GameBoard: public Subject {
    TextDisplay *td;
    GraphicsDisplay *gd;
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Link>> allLinks;
    vector<shared_ptr<AbilityCard>> allAbilityCards;

    int currPlayerIndex;
    bool currPlayerAbilityPlayed;
    int winnerIndex;
    bool isWon;
    bool graphicsEnabled;

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
        const string SP_DISPLAY_STR = "S";
        const string DATA_DISPLAY_STR = "D";
        const string VIRUS_DISPLAY_STR = "V";
        const string BORDER_DISPLAY_STR = "=";

        GameBoard();
        ~GameBoard();
        friend ostream &operator<<(ostream &out, const GameBoard &gb);
        void notifyObservers() override;

        void init();
        // void applyAbility(AbilityCard& ac, Player *player = nullptr); // TODO: same as movePiece for useAbility()
        void movePiece(shared_ptr<Link> link, Direction dir); // TODO: possibly move to private or delete bc of moveLink() below
        void battlePieces(shared_ptr<Link> linkp1, shared_ptr<Link> linkp2);
        void startNewTurn();
        void downloadIdentity(shared_ptr<Link> link1, Player *player = nullptr);
        void updateIdentity(Link& link);
        void revealLink(Link& link);

        // text command interactions
        // all methods other than playerAbilities() return a string with the error message if the method fails
        void moveLink(string linkName, string direction);
        string playerAbilities(Player& player); // unlikely to fail since there is no user input
        void useAbility(int abilityId, int xCoord, int yCoord); // for firewall, wallwall, hazeofwar
        void useAbility(int abilityID, string linkName); // for remaining abilities

        // setters
        void setLinks(unique_ptr <vector<string>> linkPlacements, shared_ptr<Player> player);
        void setAbilities(string abilities, shared_ptr<Player> player);
        void setGraphicsDisplay(GraphicsDisplay *gd);
        void addFireWall(FireWall firewall);

        // getters
        vector<shared_ptr<Player>>& getPlayers();
        unique_ptr<vector<shared_ptr<Link>>> getPlayerLinks(Player& player);
        // vector<std::shared_ptr<Link>> getAllLinks();
        // vector<AbilityCard>& getAllAbilityCards();
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
    private:
        unique_ptr<vector<shared_ptr<AbilityCard>>> getPlayerAbilities(Player& player); // possibly deletable
        shared_ptr<AbilityCard> getAbilityCard(int abilityID);
        shared_ptr<Link> findLink(string linkName, vector<shared_ptr<Link>> links);
};
#endif
