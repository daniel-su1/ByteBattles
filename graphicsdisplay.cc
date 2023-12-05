#include "graphicsdisplay.h"

#include "abilitycards/firewall.h"

GraphicsDisplay::GraphicsDisplay(Xwindow *w) : theDisplay{w} {
    if (w)
        theDisplay->fillRectangle(0, 0, BOARD_WINDOW_SIZE, 800,
                                  Xwindow::color::Black);

    std::cout << "ctor" << std::endl;
}

GraphicsDisplay::GraphicsDisplay() {}

GraphicsDisplay::~GraphicsDisplay() {
    //  delete theDisplay; 
     }

void GraphicsDisplay::drawBoardSquare(int x, int y) {
    int color =
        (y % 2)
            ? ((x % 2) ? Xwindow::color::SkyBlue : Xwindow::color::RoyalBlue)
            : ((x % 2) ? Xwindow::color::RoyalBlue : Xwindow::color::SkyBlue);
    theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                              SQUARE_SIZE, SQUARE_SIZE, color);
}

void GraphicsDisplay::drawPlayerInfoCircle(int x, int y, string info,
                                           bool isRevealed, bool virus) {
    const int CIRCLE_RADIUS = 24;
    theDisplay->fillCircle(x, y, CIRCLE_RADIUS,
                           isRevealed ? (virus ? Xwindow::color::DarkRed
                                               : Xwindow::color::DarkGreen)
                                      : Xwindow::color::Black);
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(x - 16, y + 6, info, Xwindow::color::White);
}

void GraphicsDisplay::notify(Player &p) {
    bool player = false;
    if (p.getPlayerName() == gb->P1_NAME) {
        player = true;
    }
    if(justOnAbilities){
        renderPlayerInfo(p);
        justOnAbilities = false;
    }
    else{
        theDisplay->drawRoundedRectangle(
            11, player ? 8 : 661, 478, 128, 15,
            (p.getPlayerName() ==
             (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName())
                ? Xwindow::color::Yellow
                : Xwindow::color::White);
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
                                     true,
                                     curLink->getType() == LinkType::VIRUS);
            } else {
                drawPlayerInfoCircle(
                    pLinksX, pLinksY,
                    curLink->isIdentityRevealed()
                        ? curLink->getDisplayName() + ":" +
                              std::to_string(curLink->getStrength())
                        : "?",
                    curLink->isIdentityRevealed(),
                    curLink->getType() == LinkType::VIRUS);
            }

            pLinksX += 55;
        }
    }
}

void GraphicsDisplay::drawAbilityCard(int x, int y, Xwindow::color color, int number, bool used) {
    theDisplay->fillRoundedRectangle(x, y, 80, 110, 10, used ? Xwindow::color::Grey : color);
    theDisplay->setLargerFont("courier17r");
    switch (color) {
        case Xwindow::color::LinkBoost:
            theDisplay->drawString(x + 19, y + 30, "Link",
                                   Xwindow::color::White);
            theDisplay->drawString(x + 14, y + 46, "Boost",
                                   Xwindow::color::White);
            break;
        case Xwindow::color::Firewall:
            theDisplay->drawString(x, y + 30, "Firewall",
                                   Xwindow::color::White);
            break;
        case Xwindow::color::Wall:
            theDisplay->drawString(x + 21, y + 30, "Wall",
                                   Xwindow::color::White);
            break;
        case Xwindow::color::Download:
            theDisplay->drawString(x, y + 30, "Download",
                                   Xwindow::color::White);
            break;
        case Xwindow::color::Polarize:
            theDisplay->drawString(x, y + 30, "Polarize",
                                   Xwindow::color::White);
            break;
        case Xwindow::color::Scan:
            theDisplay->drawString(x + 17, y + 30, "Scan",
                                   Xwindow::color::White);
            break;

        default:
            break;
    }
    theDisplay->setLargerFont("courier34r");
    theDisplay->drawString(x + 28, y + 90, std::to_string(number),
                           Xwindow::color::White);
}

void GraphicsDisplay::renderAbilityCards(Player &p) {
    justOnAbilities = true;
    bool player = false;
    if (p.getPlayerName() == gb->P1_NAME) {
        player = true;
    }
    theDisplay->drawFilledRoundedRectangle(
        11, player ? 8 : 661, 478, 128, 15, Xwindow::color::NavyBlue,
        (p.getPlayerName() ==
         (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName())
            ? Xwindow::color::Yellow
            : Xwindow::color::White);
    int x = 23;
    std::vector<std::shared_ptr<AbilityCard>> a = *gb->getPlayerAbilities(p).get();
    for (int i = 0; i < 5; i++) {
        switch (a.at(i)->getType()) {
            case AbilityType::LINKBOOST:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::LinkBoost, i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::FIREWALL:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Firewall,
                                i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::DOWNLOAD:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Download,
                                i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::POLARIZE:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Polarize,
                                i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::SCAN:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Scan,
                                i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::WALL:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Wall,
                                i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::BACKUP:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Scan,
                                i + 1, a.at(i)->isUsed());
                break;
            case AbilityType::MOVETWICE:
                drawAbilityCard(x, player ? 18 : 668, Xwindow::color::Scan,
                                i + 1, a.at(i)->isUsed());
                break;
            default:
                break;
        }
        x += 94;
    }
}

void GraphicsDisplay::renderPlayerInfo(Player &p) {
    bool player = false;
    if (p.getPlayerName() == gb->P1_NAME) {
        player = true;
    }
    vector<shared_ptr<Link>> playerLinks = *gb->getPlayerLinks(p);
    theDisplay->setLargerFont("courier25o");
    theDisplay->drawFilledRoundedRectangle(
        11, player ? 8 : 661, 478, 128, 15, Xwindow::color::NavyBlue,
        (p.getPlayerName() ==
         (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName())
            ? Xwindow::color::Yellow
            : Xwindow::color::White);
    theDisplay->drawString(22, player ? 40 : 690, p.getPlayerName(),
                           Xwindow::color::White);
    string pDownloads =
        "Downloaded: " + std::to_string(p.getNumDataDownloads()) +
        gb->DATA_DISPLAY_STR + ", " + std::to_string(p.getNumVirusDownloads()) +
        gb->VIRUS_DISPLAY_STR;
    string pAbilities = "Abilities: " + std::to_string(p.getAbilityCount());
    theDisplay->setLargerFont("courier20r");
    theDisplay->drawString(27, player ? 67 : 717, pDownloads.c_str(),
                           Xwindow::color::White);
    theDisplay->drawString(27, player ? 97 : 747, pAbilities.c_str(),
                           Xwindow::color::White);
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
                                 true, curLink->getType() == LinkType::VIRUS);
        } else {
            drawPlayerInfoCircle(pLinksX, pLinksY,
                                 curLink->isIdentityRevealed() ? curLink->getDisplayName() + ":" +
                                     std::to_string(curLink->getStrength()) : "?",
                                 curLink->isIdentityRevealed(),
                                 curLink->getType() == LinkType::VIRUS);
        }

        pLinksX += 55;
    }
    // renderAbilityCards(p);
}

void GraphicsDisplay::renderSquare(int x, int y, string displayName,
                                   Xwindow::color color) {
    const int BUFFER_SIZE = 23;
    int text_x = SQUARE_SIZE * x + BUFFER_SIZE;
    int text_y = SQUARE_SIZE * y + SQUARE_SIZE / 2 + BUFFER_SIZE;
    theDisplay->setLargerFont("courier34r");
    if (displayName == "a" || displayName == "b" || displayName == "c" ||
        displayName == "d" || displayName == "e" || displayName == "f" ||
        displayName == "g" || displayName == "h" || displayName == "A" ||
        displayName == "B" || displayName == "C" || displayName == "D" ||
        displayName == "E" || displayName == "F" || displayName == "G" ||
        displayName == "H") {
        theDisplay->fillCircle(SQUARE_SIZE * x + (SQUARE_SIZE / 2),
                               SQUARE_SIZE * y + 150 + (SQUARE_SIZE / 2),
                               SQUARE_SIZE / 2 - 5, Xwindow::color::Black);

        theDisplay->drawString(text_x, text_y + 140, displayName);
    } else if (displayName == gb->SP_DISPLAY_STR) {  // server ports
        theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                                  SQUARE_SIZE, SQUARE_SIZE,
                                  Xwindow::color::Yellow);
        theDisplay->drawString(text_x, text_y + 140, displayName,
                               Xwindow::color::Black);
    } else if (displayName == "X") {  // wall
        theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                                  SQUARE_SIZE, SQUARE_SIZE,
                                  Xwindow::color::Wall);
        theDisplay->drawString(text_x, text_y + 140, displayName,
                               Xwindow::color::White);
    } else {
        theDisplay->fillRectangle(SQUARE_SIZE * x, SQUARE_SIZE * y + 150,
                                  SQUARE_SIZE, SQUARE_SIZE, color);
        theDisplay->drawString(text_x, text_y + 140, displayName,
                               Xwindow::color::Black);
    }
}

void GraphicsDisplay::notify(FireWall &firewall) {
    renderSquare(firewall.getCoords().getX(), firewall.getCoords().getY(),
                 (firewall.getOwner().getPlayerName() == gb->P1_NAME)
                     ? gb->FIREWALL_P1_STR
                     : gb->FIREWALL_P2_STR,
                 Xwindow::color::Firewall);
}

void GraphicsDisplay::notify(Wall &wall) {
    renderSquare(wall.getCoords().getX(), wall.getCoords().getY(),
                 (wall.getOwner().getPlayerName() == gb->P1_NAME)
                     ? gb->WALL_STR
                     : gb->WALL_STR,
                 Xwindow::color::Wall);
}

void GraphicsDisplay::notify(Link &link) {
    int x = link.getCurrCoords().getX();
    int y = link.getCurrCoords().getY();
    int prevX = link.getPreviousCoords().getX();
    int prevY = link.getPreviousCoords().getY();
    bool firewall = false;
    bool wall = false;
    string owner = "";
    for(auto i:gb->getActiveFirewalls()){
        if (i.getCoords().getX() == prevX && i.getCoords().getY() == prevY){
                firewall = true;
                owner = i.getOwner().getPlayerName();
            }
    }
    for (auto i : gb->getActiveWalls()) {
        if (i.getCoords().getX() == prevX && i.getCoords().getY() == prevY) {
            wall = true;
            owner = i.getOwner().getPlayerName();
        }
    }

    if(firewall){
        renderSquare(prevX, prevY, owner == "Player 1" ? "m" : "w", Xwindow::color::Firewall);
    }
    if(wall){
        renderSquare(prevX, prevY, "X",
                     Xwindow::color::Wall);
    }
    else{
        drawBoardSquare(link.getPreviousCoords().getX(),
                        link.getPreviousCoords().getY());
    }

    if (x == -1 || y == -1) {
        return;
    }
    renderSquare(x, y, link.getDisplayName());
}

void GraphicsDisplay::init(GameBoard &gb) {
    std::cout << "init" << std::endl;
    this->gb = &gb;
    vector<ServerPort> sp = gb.getServerPort();
    for (int x = 0; x < gb.BOARD_SIZE; x++) {
        for (int y = 0; y < gb.BOARD_SIZE; y++) {
            if (y % 2) {
                theDisplay->fillRectangle(SQUARE_SIZE * x,
                                          SQUARE_SIZE * y + 150, SQUARE_SIZE,
                                          SQUARE_SIZE,
                                          x % 2 ? Xwindow::color::SkyBlue
                                                : Xwindow::color::RoyalBlue);
            } else {
                theDisplay->fillRectangle(SQUARE_SIZE * x,
                                          SQUARE_SIZE * y + 150, SQUARE_SIZE,
                                          SQUARE_SIZE,
                                          x % 2 ? Xwindow::color::RoyalBlue
                                                : Xwindow::color::SkyBlue);
            }
        }
    }
    for (size_t i = 0; i < sp.size(); i++) {
        int x = sp[i].getCoords().getX();
        int y = sp[i].getCoords().getY();
        renderSquare(x, y, sp[i].getDisplayName());
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
