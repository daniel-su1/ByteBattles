#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {
    theDisplay = new Xwindow(BOARD_WINDOW_SIZE, BOARD_WINDOW_SIZE);
    theDisplay->fillRectangle(0, 0, BOARD_WINDOW_SIZE, BOARD_WINDOW_SIZE, Xwindow::White);
}

GraphicsDisplay::~GraphicsDisplay() {}

void GraphicsDisplay::renderSquare(int x, int y, GamePiece& gp) {
    const int BUFFER_SIZE = 23;
    int text_x = SQUARE_SIZE * x + BUFFER_SIZE;
    int text_y = SQUARE_SIZE * y + SQUARE_SIZE / 2 + BUFFER_SIZE;
    string displayName = gp.getDisplayName();
    theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y, SQUARE_SIZE, SQUARE_SIZE, Xwindow::Black);
    theDisplay->drawString(text_x, text_y, displayName);
}

void GraphicsDisplay::notify(Link &link) {
    int x = link.getCurrCoords().getX();
    int y = link.getCurrCoords().getY();
    renderSquare(x, y, link);
    theDisplay->fillRectangle(SQUARE_SIZE * link.getPreviousCoords().getX(), SQUARE_SIZE * link.getPreviousCoords().getY(), SQUARE_SIZE, SQUARE_SIZE, Xwindow::White);
 }

void GraphicsDisplay::init(GameBoard &gb) {
    vector<ServerPort> sp = gb.getServerPort();
    for (size_t i = 0; i < sp.size(); i++) {
        int x = sp[i].getCoords().getX();
        int y = sp[i].getCoords().getY();
        renderSquare(x, y, sp[i]);
    }
}

void GraphicsDisplay::notify(GameBoard &gb) {}