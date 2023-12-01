#include "textdisplay.h"

TextDisplay::TextDisplay(){
    theDisplay = vector<vector<char>>(8, vector<char>(8, '.'));
}

void TextDisplay::notify(Link &link) {
  int x = link.getCurrCoords().getX();
  int y = link.getCurrCoords().getY();
  theDisplay[y][x] = link.getDisplayName()[0];
}

void TextDisplay::notify(GameBoard &gb) {
}

void TextDisplay::init(GameBoard& gb) {
    myGb = &gb;
    vector<ServerPort> sp = gb.getServerPort();
    for (int i = 0; i < sp.size(); i++) {
      int x = sp[i].getCoords().getX();
      int y = sp[i].getCoords().getY();
      theDisplay[y][x] = sp[i].getDisplayName()[0];
    }
}

// TO DO: change 8 to constant
ostream &operator<<(ostream &out, const TextDisplay &td) {
  // board top edge
  for (int i = 0; i < td.myGb->BOARD_SIZE; i++) {
    out << "=";
  }
  out << endl;
  // board
  for (int i = 0; i < td.myGb->BOARD_SIZE; i++) { 
    for (int j = 0; j < td.myGb->BOARD_SIZE; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  // board bottom edge
  for (int i = 0; i < td.myGb->BOARD_SIZE; i++) {
    out << "=";
  }

  return out;
}
