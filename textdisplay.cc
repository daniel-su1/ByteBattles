#include "textdisplay.h"

TextDisplay::TextDisplay(){
    theDisplay = vector<vector<char>>(8, vector<char>(8, '_'));
}

void TextDisplay::notify(Link &link) {
    cout << "I AM NOTIFIED" << endl;
}

void TextDisplay::notify(GameBoard &gb) {
    cout << "I AM NOTIFIED - BOARD" << endl;
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
