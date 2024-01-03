#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include "observer.h"
#include "gameboard.h"
#include "abilitycards/firewall.h"
#include "abilitycards/wall.h"
class GameBoard;

class TextDisplay: public Observer {
    vector<vector<char>> theDisplay; // contains empty squares, firewalls, walls, serverports
    vector<vector<char>> links; // contains the moving links
    GameBoard *myGb;
    const char EMPTY_SQUARE = '.';
 public:
    TextDisplay();
    ~TextDisplay() = default;
    void init(GameBoard& gb);

    void notify(Link &link) override;
    void notify(GameBoard &gb) override; // do nothing bc << regenerates each time
    void notify(Player &p) override; // do nothing bc << regenerates each time
    void notify(FireWall &firewall) override;
    void notify(Wall &wall) override;
    
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
