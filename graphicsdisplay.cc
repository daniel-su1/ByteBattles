#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {
    theDisplay = new Xwindow(BOARD_WINDOW_SIZE, 800);
    theDisplay->fillRectangle(0, 0, BOARD_WINDOW_SIZE, 800, Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() { delete theDisplay; }

void GraphicsDisplay::drawBoardSquare(int x, int y) {
    int color = (y % 2) ? ((x % 2) ? Xwindow::SkyBlue : Xwindow::RoyalBlue)
                        : ((x % 2) ? Xwindow::RoyalBlue : Xwindow::SkyBlue);
    theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                              SQUARE_SIZE, SQUARE_SIZE, color);
}

void GraphicsDisplay::drawPlayerInfoCircle(int x, int y, string info,
                                           bool virus) {
    const int CIRCLE_RADIUS = 24;
    theDisplay->fillCircle(x, y, CIRCLE_RADIUS,
                           virus ? Xwindow::DarkRed : Xwindow::DarkGreen);
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(x - 16, y + 6, info, Xwindow::White);
}

void GraphicsDisplay::renderPlayerInfo(Player p) {
    bool player = false;
    if (p.getPlayerName() == "Player 1") {
        player = true;
    }
    vector<shared_ptr<Link>> playerLinks = *gb->getPlayerLinks(p);
    theDisplay->setLargerFont("courier25o");
    theDisplay->drawFilledRoundedRectangle(11, player ? 8 : 661, 478, 128, 15,
                                           Xwindow::NavyBlue, Xwindow::White);
    theDisplay->drawString(22, player ? 40 : 690, p.getPlayerName(),
                           Xwindow::White);
    string pDownloads =
        "Downloaded: " + std::to_string(p.getNumDataDownloads()) + "D, " +
        std::to_string(p.getNumVirusDownloads()) + "V";
    string pAbilities = "Abilities: " + std::to_string(p.getAbilityCount());
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(27, player ? 67 : 717, pDownloads.c_str(),
                           Xwindow::White);
    theDisplay->drawString(27, player ? 97 : 747, pAbilities.c_str(),
                           Xwindow::White);
    // std::cout << "Number of links: " << player2Links.size() << std::endl;

    // for (int i = 0; i < player2Links.size(); i++) {
    //     shared_ptr<Link> curLink = player2Links[i];
    //     drawPlayerInfoCircle(
    //         p2LinksX, p2LinksY,
    //         curLink->getDisplayName() + ":" +
    //         std::to_string(curLink->getStrength()), curLink->getType() ==
    //         LinkType::virus); std::cout << "test" << endl;
    // }
    int pLinksX = 290;
    int pLinksY = player ? 45 : 695;

    for (int i = 0; i < playerLinks.size(); i++) {
        shared_ptr<Link> curLink = playerLinks[i];
        if (i == 4) {
            pLinksX = 290;
            pLinksY = player ? 103 : 748;
        }
        drawPlayerInfoCircle(pLinksX, pLinksY,
                             curLink->getDisplayName() + ":" +
                                 std::to_string(curLink->getStrength()),
                             curLink->getType() == LinkType::virus);
        pLinksX += 55;
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
    drawBoardSquare(link.getPreviousCoords().getX(),
                    link.getPreviousCoords().getY());
    if (x == -1 || y == -1) {
        return;
    }
    renderSquare(x, y, link);
    
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

    // Player &p1 = *(this->gb->getPlayers())[this->gb->getCurrPlayerIndex()];
    // Player &p2 = *(this->gb->getPlayers())[this->gb->getNextPlayerIndex()];
    // renderPlayerInfo(p1);
    // renderPlayerInfo(p2);
}

void GraphicsDisplay::notify(GameBoard &gb) { 
    renderPlayerInfo(*gb.getPlayers()[gb.getCurrPlayerIndex()]);
    renderPlayerInfo(*gb.getPlayers()[gb.getNextPlayerIndex()]);
}