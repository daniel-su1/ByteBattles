#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>

#include "abilitycards/firewall.h"
#include "abilitycards/wall.h"
#include "gameboard.h"
#include "observer.h"
#include "window.h"
class GameBoard;
class Wall;

class GraphicsDisplay : public Observer {
    Xwindow *theDisplay;
    GameBoard *gb;
    bool justOnAbilities = false;
    void renderSquare(int x, int y, string displayName, Xwindow::color color = Xwindow::color::Black);
    void drawBoardSquare(int x, int y);
    void drawPlayerInfoCircle(int x, int y, string info, bool isRevealed, bool virus);
    void drawAbilityCard(int x, int y, Xwindow::color color, int number, bool used);
    public: 
    void renderAbilityCards(Player &p);
    void renderPlayerInfo(Player &p);
    const int BOARD_WINDOW_SIZE = 500;
    const int SQUARE_SIZE = BOARD_WINDOW_SIZE /8;
    GraphicsDisplay(Xwindow *w);
    GraphicsDisplay();
    ~GraphicsDisplay();
    void notify(Link &link) override;
    void notify(GameBoard &gb) override;
    void init(GameBoard &gb);
    void notify(Player &p);
    void notify(FireWall &firewall);
    void notify(Wall &wall);
};

#endif
