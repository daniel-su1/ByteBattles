#ifndef COORDS_H
#define COORDS_H

class Coords { 
    int x;
    int y;
    public:
        Coords(int x, int y);
        // accessor/gettor function that returns x
        int getX();
        // accessor/gettor function that returns y
        int getY();
        // setter functions 
        void setX(int newX);
        void setY(int newY);
        bool operator==(Coords& rhs);
};

#endif
