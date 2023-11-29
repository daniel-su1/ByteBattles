#include "serverport.h"

Coords ServerPort::getCoords() {
    return coords;
}

ServerPort::ServerPort(Coords coords): SpecialCoord(coords) {

}
