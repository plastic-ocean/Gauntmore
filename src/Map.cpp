#include "Map.h"
#include "Room.h"


/**
* Constructor.
*/
Map::Map(int size) {
    _room = new Room(3, size);
    _rooms.push_back(_room);
}

void Map::changeRoom(int edge) {
    // if exit has not been used
    int size = getRoom()->getSize();
    _room = new Room(3, size);
    _rooms.push_back(_room);
    // else
    // find room and switch
}
