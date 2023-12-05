#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(Xwindow *w): theDisplay{w} {
    if(w) theDisplay->fillRectangle(0, 0, BOARD_WINDOW_SIZE, 800, Xwindow::Black);

    std::cout << "ctor" << std::endl;
}

GraphicsDisplay::GraphicsDisplay(){

}

GraphicsDisplay::~GraphicsDisplay() { delete theDisplay; }

void GraphicsDisplay::drawBoardSquare(int x, int y) {
    int color = (y % 2) ? ((x % 2) ? Xwindow::SkyBlue : Xwindow::RoyalBlue)
                        : ((x % 2) ? Xwindow::RoyalBlue : Xwindow::SkyBlue);
    theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                              SQUARE_SIZE, SQUARE_SIZE, color);
}

void GraphicsDisplay::drawPlayerInfoCircle(int x, int y, string info,
                                           bool isRevealed, bool virus) {
    const int CIRCLE_RADIUS = 24;
    theDisplay->fillCircle(x, y, CIRCLE_RADIUS,
                           isRevealed
                               ? (virus ? Xwindow::DarkRed : Xwindow::DarkGreen)
                               : Xwindow::Black);
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(x - 16, y + 6, info, Xwindow::White);
}

void GraphicsDisplay::notify(Player &p) {
    bool player = false;
    if (p.getPlayerName() == "Player 1") {
        player = true;
    }
    theDisplay->drawRoundedRectangle(
        11, player ? 8 : 661, 478, 128, 15,
        (p.getPlayerName() ==
         (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName())
            ? Xwindow::Yellow
            : Xwindow::White);
    vector<shared_ptr<Link>> playerLinks = *gb->getPlayerLinks(p);
    int pLinksX = 290;
    int pLinksY = player ? 45 : 695;
    for (size_t i = 0; i < playerLinks.size(); i++) {
        shared_ptr<Link> curLink = playerLinks[i];
        if (i == 4) {
            pLinksX = 290;
            pLinksY = player ? 103 : 748;
        }
        if (p.getPlayerName() ==
            (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName()) {
            drawPlayerInfoCircle(pLinksX, pLinksY,
                                 curLink->getDisplayName() + ":" +
                                     std::to_string(curLink->getStrength()),
                                 true, curLink->getType() == LinkType::virus);
        } else {
            drawPlayerInfoCircle(
                pLinksX, pLinksY,
                curLink->isIdentityRevealed()
                    ? curLink->getDisplayName() + ":" +
                          std::to_string(curLink->getStrength())
                    : "?",
                curLink->isIdentityRevealed(),
                curLink->getType() == LinkType::virus);
        }

        pLinksX += 55;
    }
}



void GraphicsDisplay::renderPlayerInfo(Player p) {
    std::cout <<"renderplayerinfo" << std::endl;
    bool player = false;
    if (p.getPlayerName() == "Player 1") {
        player = true;
    }
    vector<shared_ptr<Link>> playerLinks = *gb->getPlayerLinks(p);
    theDisplay->setLargerFont("courier25o");
    theDisplay->drawFilledRoundedRectangle(
        11, player ? 8 : 661, 478, 128, 15, Xwindow::NavyBlue,
        (p.getPlayerName() ==
         (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName())
            ? Xwindow::Yellow
            : Xwindow::White);
    theDisplay->drawString(22, player ? 40 : 690, p.getPlayerName(),
                           Xwindow::White);
    string pDownloads =
        "Downloaded: " + std::to_string(p.getNumDataDownloads()) + gb->DATA_DISPLAY_STR + ", " +
        std::to_string(p.getNumVirusDownloads()) + gb->VIRUS_DISPLAY_STR;
    string pAbilities = "Abilities: " + std::to_string(p.getAbilityCount());
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(27, player ? 67 : 717, pDownloads.c_str(),
                           Xwindow::White);
    theDisplay->drawString(27, player ? 97 : 747, pAbilities.c_str(),
                           Xwindow::White);
    int pLinksX = 290;
    int pLinksY = player ? 45 : 695;

    for (size_t i = 0; i < playerLinks.size(); i++) {
        shared_ptr<Link> curLink = playerLinks[i];
        if (i == 4) {
            pLinksX = 290;
            pLinksY = player ? 103 : 748;
        }
        if (p.getPlayerName() ==
            (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName()) {
            drawPlayerInfoCircle(pLinksX, pLinksY,
                                 curLink->getDisplayName() + ":" +
                                     std::to_string(curLink->getStrength()),
                                 true, curLink->getType() == LinkType::virus);
        } else {
            drawPlayerInfoCircle(pLinksX, pLinksY,
                                 curLink->isIdentityRevealed() ? curLink->getDisplayName() + ":" +
                                     std::to_string(curLink->getStrength()) : "?",
                                 curLink->isIdentityRevealed(),
                                 curLink->getType() == LinkType::virus);
        }

        pLinksX += 55;
    }
}

void GraphicsDisplay::renderSquare(int x, int y, GamePiece &gp) {
    const int BUFFER_SIZE = 23;
    int text_x = SQUARE_SIZE * x + BUFFER_SIZE;
    int text_y = SQUARE_SIZE * y + SQUARE_SIZE / 2 + BUFFER_SIZE;
    theDisplay->setLargerFont("courier34r");
    string displayName = gp.getDisplayName();
    if(gb == nullptr){
        std::cout << "null" << endl;
    }
    if (displayName == gb->SP_DISPLAY_STR) {  // server ports
        theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                                  SQUARE_SIZE, SQUARE_SIZE, Xwindow::Yellow);
        theDisplay->drawString(text_x, text_y + 140, displayName,
                               Xwindow::Black);
    } 
    else {
        drawBoardSquare(x, y);
        theDisplay->fillCircle(SQUARE_SIZE * x + (SQUARE_SIZE / 2),
                               SQUARE_SIZE * y + 150 + (SQUARE_SIZE / 2),
                               SQUARE_SIZE / 2 - 5, Xwindow::Black);
        theDisplay->drawString(text_x, text_y + 140, displayName);
    }
}

void GraphicsDisplay::notify(Firewall &firewall) {
    
}


void GraphicsDisplay::notify(Link &link) {
    std::cout << "notify link" << std::endl;
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
    std::cout << "init" << std::endl;
    this->gb = &gb;
    vector<ServerPort> sp = gb.getServerPort();
    for (int x = 0; x < gb.BOARD_SIZE; x++) {
        for (int y = 0; y < gb.BOARD_SIZE; y++) {
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
