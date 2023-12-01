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
    vector<unique_ptr<Link>> allBoardPieces;
    vector<unique_ptr<AbilityCard>> allAbilityCards;
    Player* currPlayer;
    Player* winner;
    vector<Coords> boardBoundaries;
    vector<EdgeCoord> edgeCoords;
    vector<ServerPort> serverPorts;
    vector<FireWall> activeFirewalls;
    public:
        GameBoard();
        ~GameBoard();
        void notifyObservers() override;
        friend std::ostream &operator<<(std::ostream &out, const GameBoard &gd);

        void init();
        void applyAbility(AbilityCard& ac, Player *player = nullptr);
        void movePiece(string linkName, string dir);
        void movePiece(Link &link, Direction dir); // TODO: check if acc needed
        void battlePieces(Link &linkp1, Link &linkp2);
        void startNewTurn();
        void downloadIdentity(Link &link1, Player *player);
        void updateIdentity(Link& link);
        string playerAbilities(Player&);

        void setAbilities(string abilities, Player *player);
        void setLinks(unique_ptr <vector<string>> linkPlacements, Player *player);

        vector<Player>& getPlayers();
        vector<Link>& getAllBoardPieces();
        vector<AbilityCard>& getAllAbilityCards();
        Player& getCurrPlayer();
        Player& getWinner();
        vector<Coords>& getBoardBoundaries();
        vector<EdgeCoord>& getEdgeCoords();
        vector<ServerPort>& getServerPort();
        vector<FireWall>& getActiveFirewalls();
};
#endif
