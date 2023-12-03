#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {
    theDisplay = new Xwindow(BOARD_WINDOW_SIZE, 800);
    theDisplay->fillRectangle(0, 0, BOARD_WINDOW_SIZE, BOARD_WINDOW_SIZE, Xwindow::White);
}

GraphicsDisplay::~GraphicsDisplay() {}

void GraphicsDisplay::drawBoardSquare(int x, int y) {
    int color = (y % 2) ? ((x % 2) ? Xwindow::SkyBlue : Xwindow::RoyalBlue)
                        : ((x % 2) ? Xwindow::RoyalBlue : Xwindow::SkyBlue);
    theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                              SQUARE_SIZE, SQUARE_SIZE, color);
}

void GraphicsDisplay::renderSquare(int x, int y, GamePiece& gp) {
    const int BUFFER_SIZE = 23;
    int text_x = SQUARE_SIZE * x + BUFFER_SIZE;
    int text_y = SQUARE_SIZE * y + SQUARE_SIZE / 2 + BUFFER_SIZE;
    string displayName = gp.getDisplayName();
    if(displayName == "S"){
        theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                                  SQUARE_SIZE, SQUARE_SIZE, Xwindow::Yellow);
        theDisplay->drawString(text_x, text_y + 140, displayName, Xwindow::Black);
    }
    else{
        drawBoardSquare(x, y);
        theDisplay->fillCircle(SQUARE_SIZE * x + (SQUARE_SIZE / 2),
                               SQUARE_SIZE * y + 150 + (SQUARE_SIZE / 2),
                               SQUARE_SIZE / 2 - 5, Xwindow::Black);
        theDisplay->drawString(text_x, text_y + 140, displayName);
    }
}

void GraphicsDisplay::notify(Link &link) {
    int x = link.getCurrCoords().getX();
    int y = link.getCurrCoords().getY();
    renderSquare(x, y, link);
    drawBoardSquare(link.getPreviousCoords().getX(), link.getPreviousCoords().getY());
 }

void GraphicsDisplay::init(GameBoard &gb) {
    vector<ServerPort> sp = gb.getServerPort();
    for(size_t x = 0; x < gb.BOARD_SIZE; x++){
        for(size_t y = 0; y < gb.BOARD_SIZE; y++){
            if(y % 2){
                theDisplay->fillRectangle(
                    SQUARE_SIZE * x, SQUARE_SIZE * y + 150, SQUARE_SIZE,
                    SQUARE_SIZE, x % 2 ? Xwindow::SkyBlue : Xwindow::RoyalBlue);
            }
            else{
                theDisplay->fillRectangle(
                    SQUARE_SIZE * x, SQUARE_SIZE * y + 150, SQUARE_SIZE,
                    SQUARE_SIZE, x % 2 ? Xwindow::RoyalBlue : Xwindow::SkyBlue);
            }
        }
    }
    for (size_t i = 0; i < sp.size(); i++) {
        int x = sp[i].getCoords().getX();
        int y = sp[i].getCoords().getY();
        renderSquare(x, y, sp[i]);
    }
}

void GraphicsDisplay::notify(GameBoard &gb) {}