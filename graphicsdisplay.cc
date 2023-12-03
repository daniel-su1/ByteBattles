#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {

        theDisplay = new Xwindow(BOARD_WINDOW_SIZE, 800);
        theDisplay->fillRectangle(0, 0, BOARD_WINDOW_SIZE, 800, Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() {
    delete theDisplay;
}

void GraphicsDisplay::drawBoardSquare(int x, int y) {
    int color = (y % 2) ? ((x % 2) ? Xwindow::SkyBlue : Xwindow::RoyalBlue)
                        : ((x % 2) ? Xwindow::RoyalBlue : Xwindow::SkyBlue);
    theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                              SQUARE_SIZE, SQUARE_SIZE, color);
}

void GraphicsDisplay::drawPlayerInfoCircle(int x, int y, string info,
                                           bool virus) {
    const int CIRCLE_RADIUS = 11;
    theDisplay->fillCircle(x, y, CIRCLE_RADIUS,
                           virus ? Xwindow::Red : Xwindow::LimeGreen);
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(27, 747, info, Xwindow::White);
}

void GraphicsDisplay::renderPlayerInfo() {
    Player &p1 = *(gb->getPlayers())[gb->getCurrPlayerIndex()];
    Player &p2 = *(gb->getPlayers())[gb->getNextPlayerIndex()];

    vector<shared_ptr<Link>> player2Links = *(gb->getPlayerLinks(p2));
    
    int p2LinksX = 256;
    int p2LinksY = 712;
    theDisplay->setLargerFont("courier25o");
    // theDisplay->drawString(32, 32, p1.getPlayerName(), Xwindow::White);
    theDisplay->drawString(22, 690, p2.getPlayerName(), Xwindow::White);
    string p2Downloads =
        "Downloaded: " + std::to_string(p2.getNumDataDownloads()) + "D, " +
        std::to_string(p2.getNumVirusDownloads()) + "V";
    string p2Abilities = "Abilities: " + std::to_string(p2.getAbilityCount());
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(27, 717, p2Downloads.c_str(), Xwindow::White);
    theDisplay->drawString(27, 747, p2Abilities.c_str(), Xwindow::White);
    std::cout << "test1" << endl;
    std::cout << "Number of links: " << player2Links.size() << std::endl;

    for (int i = 0; i < player2Links.size(); i++) {
        shared_ptr<Link> curLink = player2Links[i];
        drawPlayerInfoCircle(
            p2LinksX, p2LinksY,
            curLink->getDisplayName() + ":" + std::to_string(curLink->getStrength()),
            curLink->getType() == LinkType::virus);
            std::cout << "test" << endl;
    }
}

void GraphicsDisplay::renderSquare(int x, int y, GamePiece &gp) {
    const int BUFFER_SIZE = 23;
    int text_x = SQUARE_SIZE * x + BUFFER_SIZE;
    int text_y = SQUARE_SIZE * y + SQUARE_SIZE / 2 + BUFFER_SIZE;
    theDisplay->setLargerFont("courier34r");
    string displayName = gp.getDisplayName();
    if (displayName == "S") {
        theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                                  SQUARE_SIZE, SQUARE_SIZE, Xwindow::Yellow);
        theDisplay->drawString(text_x, text_y + 140, displayName,
                               Xwindow::Black);
    } else {
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
    drawBoardSquare(link.getPreviousCoords().getX(),
                    link.getPreviousCoords().getY());
}

void GraphicsDisplay::init(GameBoard &gb) {
    this->gb = &gb;
    vector<ServerPort> sp = gb.getServerPort();
    for (size_t x = 0; x < gb.BOARD_SIZE; x++) {
        for (size_t y = 0; y < gb.BOARD_SIZE; y++) {
            if (y % 2) {
                theDisplay->fillRectangle(
                    SQUARE_SIZE * x, SQUARE_SIZE * y + 150, SQUARE_SIZE,
                    SQUARE_SIZE, x % 2 ? Xwindow::SkyBlue : Xwindow::RoyalBlue);
            } else {
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

void GraphicsDisplay::notify(GameBoard &gb) {
    renderPlayerInfo();
}