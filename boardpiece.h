#ifndef BOARDPIECE_H
#define BOARDPIECE_H
#include "gamepiece.h"
#include "coords.h"
enum Direction {Up, Down, Left, Right}; 
class BoardPiece: public GamePiece { // add public: GamePiece later
    protected:
    int stepSize;
    Coords prevCords;
    Coords currCoords;
    public:
    // sets new stepsize for the piece's movement
    virtual void setStepSize(int newStepSize) = 0;
    // moves the piece stepsize amount of steps in given direction
    virtual void movePiece(Direction direction) = 0;
    // returns the previous coords of the piece
    virtual Coords getPreviousCoords() = 0;
    // returns the curr coords of the piece
    virtual Coords getCurrCoords() = 0;
};

#endif
