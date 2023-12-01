#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {
    theDisplay->fillRectangle(0, 0, 500, 500, Xwindow::Black);
}

void GraphicsDisplay::notify(Link &link) { 
    
 }

void GraphicsDisplay::notify(GameBoard &gb) {
    vector<ServerPort> sp = gb.getServerPort();
    for (int i = 0; i < sp.size(); i++) {
        int x = sp[i].getCoords().getX();
        int y = sp[i].getCoords().getY();
        theDisplay[x][y] = sp[i].getDisplayName()[0];
    }
}
