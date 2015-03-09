#include <iostream>
#include "Map.h"
#include "MazeGen.h"

using namespace std;


/**
 * Constructor.
 */
Map::Map(int size) {
    spMazeGen mazeGen = new MazeGen(size);
    setRoomMap(static_cast<vector<vector<spRoom>>>(mazeGen->generate()));
    
    _entrance = mazeGen->getEntrance();
    setRow(_entrance.first);
    setCol(_entrance.second);

    _room = _roomMap[_row][_col];

    string tmxFile = _getTmxFile();

    _room->createTileMap(tmxFile);
}


/**
 * Sets the current room a new room in the maze depending the given wall edge.
 *
 * @edge is the wall edge of the last room the player existed.
 */
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


/**
 * Gets the current room.
 */
spRoom Map::getRoom() {
    return _room;
}


/**
 * Sets the current room.
 */
void Map::setRoom(spRoom &room) {
    _room = room;
}


/**
 * Gets the room map.
 */
vector<vector<spRoom>> Map::getRoomMap() {
    return _roomMap;
}


/**
 * Sets the room map.
 */
void Map::setRoomMap(vector<vector<spRoom>> roomMap) {
    _roomMap = roomMap;
}


/**
 * Gets the current column in the maze.
 */
int Map::getCol() const {
    return _col;
}


/**
 * Sets the current column in the maze.
 */
void Map::setCol(int col) {
    Map::_col = col;
}


/**
 * Gets the current row in the maze.
 */
int Map::getRow() const {
    return _row;
}

/**
 * Sets the current row in the maze.
 */
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