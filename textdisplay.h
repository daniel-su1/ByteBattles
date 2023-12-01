#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include "observer.h"
#include "gameboard.h"

class TextDisplay: public Observer {
    vector<vector<char>> theDisplay; 
    GameBoard *gb;
 public:
    TextDisplay();
    void init(GameBoard& gb);
    ~TextDisplay() = default;
    void notify(Link& link) override;
    void notify(GameBoard& gb) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
