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
    setRoomMap(static_cast<vector<vector<spRoom>>>(mazeGen->generate()));
    
    _entrance = mazeGen->getEntrance();
    setRow(_entrance.first);
    setCol(_entrance.second);

    _room = _roomMap[_row][_col];

//    _room = new Room(turn, 15, {true, true, false, false});

    _room->createTileMap();
}


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

    setRoom(_roomMap[_row][_col]);
    _room->createTileMap();
}