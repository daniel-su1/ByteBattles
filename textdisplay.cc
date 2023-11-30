#include "textdisplay.h"

TextDisplay::TextDisplay(){
    theDisplay = vector<vector<char>>(8, vector<char>(8, '_'));
}

void TextDisplay::notify(Link &link) {
  cout << "I AM NOTIFIED OF A LINK";
}

void TextDisplay::notify(GameBoard &gb) {
  vector<ServerPort> sp = gb.getServerPort();
  for (int i = 0; i < sp.size(); i++) {
    int x = sp[i].getCoords().getX();
    int y = sp[i].getCoords().getY();
    theDisplay[x][y] = sp[i].getDisplayName()[0];
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 8; i++) { 
    for (int j = 0; j < 8; j++) {
      out << td.theDisplay[i][j];
    }
    if (i != 8 - 1) {
    out << endl;
    }
  }
  return out;
}
