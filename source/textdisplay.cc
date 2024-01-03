#include "textdisplay.h"

TextDisplay::TextDisplay(){
    theDisplay = vector<vector<char>>(8, vector<char>(8, EMPTY_SQUARE));
    links = vector<vector<char>>(8, vector<char>(8, EMPTY_SQUARE));
}

void TextDisplay::notify(GameBoard &gb) {}

void TextDisplay::notify(Player& p) {}

void TextDisplay::notify(Link &link) {

  int x = link.getCurrCoords().getX();
  int y = link.getCurrCoords().getY();
  if (x != -1 && y != -1) {
    links[y][x] = link.getDisplayName()[0];
  }
  
  int prevX = link.getPreviousCoords().getX();
  int prevY = link.getPreviousCoords().getY();
  if (prevX != -1 && prevY != -1) {
    links[prevY][prevX] = EMPTY_SQUARE;
  }

}

void TextDisplay::notify(FireWall& firewall) {
  int x = firewall.getCoords().getX();
  int y = firewall.getCoords().getY();
  theDisplay[y][x] = firewall.getOwner().getPlayerName() == myGb->P1_NAME 
    ? myGb->FIREWALL_P1_STR[0] 
    : myGb->FIREWALL_P2_STR[0];
}

void TextDisplay::notify(Wall &wall) {
    int x = wall.getCoords().getX();
    int y = wall.getCoords().getY();
    theDisplay[y][x] = wall.getOwner().getPlayerName() == myGb->P1_NAME
                           ? myGb->FIREWALL_P1_STR[0]
                           : myGb->FIREWALL_P2_STR[0];
}

void TextDisplay::init(GameBoard &gb) {
    myGb = &gb;
    vector<ServerPort> sp = gb.getServerPort();
    for (size_t i = 0; i < sp.size(); i++) {
      int x = sp[i].getCoords().getX();
      int y = sp[i].getCoords().getY();
      theDisplay[y][x] = sp[i].getDisplayName()[0];
    }
}

void printPlayerInfo(Player& p, GameBoard* gb, ostream& out) {
  out << p.getPlayerName() << ":" << endl;
  out << "Downloaded: " << p.getNumDataDownloads() << gb->DATA_DISPLAY_STR << ", " << p.getNumVirusDownloads() << gb->VIRUS_DISPLAY_STR << endl;
  out << "Abilities: " << p.getAbilityCount() << endl;
  vector<shared_ptr<Link>> playerLinks = *gb->getPlayerLinks(p);
  for (size_t i = 0; i < playerLinks.size(); i++) {
    if (i == playerLinks.size() / 2) { // halfway point
      out << "\n";
    }
    shared_ptr<Link> curLink = playerLinks[i];
    out << curLink->getDisplayName() << ": ";
    if (curLink->isIdentityRevealed() ||
        p.getPlayerName() ==
            (*gb->getPlayers()[gb->getCurrPlayerIndex()]).getPlayerName()) {
        out << curLink->typeAndStrength << " ";
    } else {
        out << "? ";
    }
  }
  out << endl;
}

void printBoardBoundaries(int boundarySize, ostream& out) {
  for (int i = 0; i < boundarySize; i++) {
    out << "=";
  }
  out << endl;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  Player &p1 = *(td.myGb->getPlayers())[0];
  Player &p2 = *(td.myGb->getPlayers())[1];
  // player 1
  printPlayerInfo(p1, td.myGb, out);
  // board top edge
  printBoardBoundaries(td.myGb->BOARD_SIZE, out);
  // board
  for (int i = 0; i < td.myGb->BOARD_SIZE; i++) { 
    for (int j = 0; j < td.myGb->BOARD_SIZE; j++) {
      if (td.links[i][j] != td.EMPTY_SQUARE) {
        // place links on top of empty squares/firewalls
        out << td.links[i][j];
      } else {
        out << td.theDisplay[i][j];
      }
    }
    out << endl;
  }
  // board bottom edge
  printBoardBoundaries(td.myGb->BOARD_SIZE, out);
  // player 2
  printPlayerInfo(p2, td.myGb, out);
  return out;
}

