#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>

#include "gameboard.h"
#include "observer.h"
#include "window.h"

class GraphicsDisplay : public Observer {
    Xwindow *theDisplay;
    GameBoard *gb;
    void renderSquare(int x, int y, GamePiece& gp);
    void renderPlayerInfo(Player p);
    void drawBoardSquare(int x, int y);
    void drawPlayerInfoCircle(int x, int y, string info, bool isRevealed, bool virus);
   public:
    const int BOARD_WINDOW_SIZE = 500;
    const int SQUARE_SIZE = BOARD_WINDOW_SIZE /8;
    GraphicsDisplay(Xwindow *w);
    GraphicsDisplay();
    ~GraphicsDisplay();
    void notify(Link &link) override;
    void notify(GameBoard &gb) override;
    void init(GameBoard &gb);
    void notify(Player &p);
};

#endif
