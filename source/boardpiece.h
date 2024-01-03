#ifndef BOARDPIECE_H
#define BOARDPIECE_H
#include "gamepiece.h"
#include "coords.h"
enum Direction {Up, Down, Left, Right}; 
class BoardPiece: public GamePiece { // add public: GamePiece later
    protected:
        int stepSize;
        Coords prevCoords;
        Coords currCoords;
    public:
        BoardPiece(int stepSize, Coords currCoords, Player& owner, string displayName);
        // sets new stepsize for the piece's movement
        void setStepSize(int newStepSize);
        // reverts piece to previous location
        void backupStep();
        // moves the piece stepsize amount of steps in given direction
        void movePiece(Direction direction);
        // returns the previous coords of the piece
        Coords getPreviousCoords();
        // returns the curr coords of the piece
        Coords getCurrCoords();
        void downloadLink();

};

#endif
