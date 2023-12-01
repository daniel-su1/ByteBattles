#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>

#include "cell.h"
#include "gameboard.h"
#include "observer.h"
#include "window.h"

class GraphicsDisplay : public Observer {
    Xwindow *theDisplay;
    GameBoard *gb;

   public:
    GraphicsDisplay();
    ~GraphicsDisplay() = default;
    void notify(Link &link) override;
    void notify(GameBoard &gb) override;
};

#endif