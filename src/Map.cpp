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

    string tmxFile = _getTmxFile();

    _room->createTileMap(tmxFile);
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

    string tmxFile = _getTmxFile();
    _room->createTileMap(tmxFile);
}


spRoom Map::getRoom() {
    return _room;
}

void Map::setRoom(spRoom &room) {
    _room = room;
}

vector<vector<spRoom>> Map::getRoomMap() {
    return _roomMap;
}

void Map::setRoomMap(vector<vector<spRoom>> roomMap) {
    _roomMap = roomMap;
}

int Map::getCol() const {
    return _col;
}

void Map::setCol(int col) {
    Map::_col = col;
}

int Map::getRow() const {
    return _row;
}

void Map::setRow(int row) {
    Map::_row = row;
}


/**
* Checks if the current room is an outside room.
*
* @return a file string.
*/
string Map::_getTmxFile() {
    string tmxFile = "";
    if (_row == 0) {
        // top
        tmxFile = "tmx/outside_top.tmx";
    } else if (_col == _room->getSize() - 1) {
        // right
        tmxFile = "tmx/outside_right.tmx";
    } else if (_row == _room->getSize() - 1) {
        // bottom
        tmxFile = "tmx/outside_bottom.tmx";
    } else if (_col == 0) {
        // left
        tmxFile = "tmx/outside_left.tmx";
    }
    return tmxFile;
}