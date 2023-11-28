#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include "observer.h"
#include "gameboard.h"

class TextDisplay: public Observer {
    vector<vector<char>> theDisplay; 
    GameBoard *gb;
 public:
    void notify(Link& link) override;
    void notify(GameBoard& gb) override;
};

#endif
