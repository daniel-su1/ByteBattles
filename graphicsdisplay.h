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

   public:
    GraphicsDisplay();
    ~GraphicsDisplay();
    void notify(Link &link) override;
    void notify(GameBoard &gb) override;
    void init(GameBoard &gb);
};

#endif