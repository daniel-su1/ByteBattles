#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {
    theDisplay = new Xwindow(500, 500);
    theDisplay->fillRectangle(0, 0, 500, 500, Xwindow::White);
}

GraphicsDisplay::~GraphicsDisplay() {}

void GraphicsDisplay::notify(Link &link) {
    int x = link.getCurrCoords().getX();
    int y = link.getCurrCoords().getY();
    theDisplay->fillRectangle(62.5 * x, 62.5 * y, 62.5, 62.5, Xwindow::Black);
    theDisplay->drawString(62.5 * x, 62.5 * y, link.getDisplayName());
 }

void GraphicsDisplay::init(GameBoard &gb) {
    vector<ServerPort> sp = gb.getServerPort();
    for (size_t i = 0; i < sp.size(); i++) {
        int x = sp[i].getCoords().getX();
        int y = sp[i].getCoords().getY();
        int text_x = 62.5 * x + 23;
        int text_y = 62.5 * y + (62.5/2) + 12;
        string displayName = sp[i].getDisplayName();
        theDisplay->fillRectangle(62.5*x, 62.5 * y, 62.5, 62.5, Xwindow::Black);
        theDisplay->drawString(text_x, text_y, displayName);
    }
}

void GraphicsDisplay::notify(GameBoard &gb) {}