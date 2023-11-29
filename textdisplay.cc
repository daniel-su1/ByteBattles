#include "textdisplay.h"

void TextDisplay::notify(Link &link) {
    cout << "I AM NOTIFIED" << endl;
}

void TextDisplay::notify(GameBoard &gb) {
    cout << "I AM NOTIFIED - BOARD" << endl;
}



