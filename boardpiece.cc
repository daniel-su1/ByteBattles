#include "boardpiece.h"

BoardPiece::BoardPiece(int stepSize, Coords currCoords, Player& owner,
                       string displayName)
    : GamePiece(owner, displayName),
      stepSize{1},
      prevCoords(Coords(-1, -1)),
      currCoords(currCoords) {}

Coords BoardPiece::getPreviousCoords() { return prevCoords; }

Coords BoardPiece::getCurrCoords() { return currCoords; }

void BoardPiece::backupStep() {
    if (prevCoords.getX() == -1 || prevCoords.getX() == -1) {
        return;
    }
    Coords temp = currCoords;
    currCoords = prevCoords;
    prevCoords = temp;
}

void BoardPiece::movePiece(Direction direction) {    
    prevCoords = currCoords;
    if (direction == Left) { 
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
    }
}

void BoardPiece::downloadLink() {
    prevCoords = currCoords;
    currCoords.setX(-1);
    currCoords.setY(-1);
}

void BoardPiece::setStepSize(int newStepSize) { stepSize = newStepSize; }
