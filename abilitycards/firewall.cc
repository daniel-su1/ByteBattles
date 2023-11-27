#include "firewall.h"
#include "iostream"
using namespace std;

void FireWall::activate() {
    cout << "FIREWALL WOOSH" << endl; 
}

Coords FireWall::getCoords() {
    return coords;
}

