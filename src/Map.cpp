#include <iostream>
#include "Map.h"
#include "MazeGen.h"

using namespace std;

/**
* Constructor.
*/
Map::Map(int size) {
    // TODO mini-map: store two copies of maze matrix and change all tiles in one to "explored" only when visited by player
    spMazeGen mazeGen = new MazeGen(size);
    _roomMap = mazeGen->generate();
    
    _entrance = mazeGen->getEntrance();
    _row = static_cast<int>(_entrance.x);
    _col = static_cast<int>(_entrance.y);

    _room = _roomMap[_row][_col];

//    _room = new Room(turn, 15, {true, true, false, false});

    _room->createTileMap();

//    _room->printMap();
//    cout << "entrance: " << _row << ", " << _col << endl;
}


//int Map::getSize(){
//    return _size * 32;
//}


void Map::changeRoom(int edge) {
    switch (edge) {
        case 0: // top
            _row--;
            break;
        case 1: // right
            _col++;
            break;
        case 2: // bottom
            _row++;
            break;
        case 3: // left
            _col--;
            break;
        default:
            break;
    }

//    cout << "new room: " << _row << ", " << _col << endl;
    setRoom(_roomMap[_row][_col]);
    _room->createTileMap();
}