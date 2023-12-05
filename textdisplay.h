#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include "observer.h"
#include "gameboard.h"
#include "abilitycards/firewall.h"
#include "abilitycards/wall.h"
class GameBoard;
class Wall;

class TextDisplay: public Observer {
    vector<vector<char>> theDisplay; 
    GameBoard *myGb;
 public:
    TextDisplay();
    void init(GameBoard& gb);
    ~TextDisplay() = default;
    void notify(Link& link) override;
    void notify(GameBoard& gb) override;
    void notify(FireWall& firewall);
    void notify(Wall& wall);
    void updateGrid(int x, int y, char c);
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
