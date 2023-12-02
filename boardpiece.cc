#include "boardpiece.h"

BoardPiece::BoardPiece(int stepSize, Coords currCoords, Player& owner,
                       string displayName)
    : GamePiece(owner, displayName),
      stepSize{1},
      prevCords(Coords(-1, -1)),
      currCoords(currCoords) {}

Coords BoardPiece::getPreviousCoords() { return prevCords; }

Coords BoardPiece::getCurrCoords() { return currCoords; }

void BoardPiece::movePiece(Direction direction) {
    prevCords = currCoords;
    if (direction == Left) {  // TODO: implement checking for moves
        int newX = currCoords.getX() - stepSize;
        currCoords.setX(newX);
    } else if (direction == Right) {
        int newX = currCoords.getX() + stepSize;
        currCoords.setX(newX);
    } else if (direction == Up) {
        int newY = currCoords.getY() - stepSize;
        currCoords.setY(newY);
    } else if (direction == Down) {
        int newY = currCoords.getY() + stepSize;
        currCoords.setY(newY);
        cout << currCoords.getY();
    }
}

void BoardPiece::setStepSize(int newStepSize) { stepSize = newStepSize; }