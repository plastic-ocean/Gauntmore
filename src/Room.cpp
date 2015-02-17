#include <iostream>
#include <fstream>
#include <random>
#include "Room.h"

using namespace std;

enum RoomType {deadend, straight, turn, branch, intersection};

Room::Room() {}

Room::Room(int type, int size, vector<bool> exitBools):
        _type(type), _size(size), _wallListSize(0), _floorListSize(0), _top(0), _right(0), _bottom(0), _left(0), _exitBools(exitBools) {
    // Seed rand.
    random_device randomDevice;
    srand(randomDevice.operator()());

    // Initialize the map.
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _map[i][j] = '@';
        }
    }

    // Initialize the lists.
    for (int i = 0; i < _maxListSize; ++i) {
        _wallList[i][0] = 0;
        _wallList[i][1] = 0;

        _floorList[i][0] = 0;
        _floorList[i][1] = 0;
    }

    createRoom();
}


/**
* Creates a room map.
*
* @type is the room type.
*/
void Room::createRoom() {
    switch(_type) {
        case deadend:
            _createDeadEnd();
            break;
        case straight:
            _createStraight();
            break;
        case turn:
            _createTurn();
            break;
        case branch:
            _createBranch();
            break;
        case intersection:
            _createIntersection();
            break;
        default:
            break;
    }

    createTileMap();
//    printMap();
}


/**
* Creates a tile map (.tmx file) from the 2D map array.
*/
void Room::createTileMap() {
    ofstream tmxFile;
    tmxFile.open("tmx/room.tmx");

    int tileSize = 32;

    if (tmxFile.is_open()) {
        tmxFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        tmxFile << "<map version=\"1.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"" << _size << "\" height=\"" << _size << "\" tilewidth=\"" << tileSize << "\" tileheight=\"" << tileSize << "\" nextobjectid=\"1\">" << endl;
        tmxFile << " <tileset firstgid=\"1\" name=\"floor\" tilewidth=\"" << tileSize << "\" tileheight=\"" << tileSize << "\">" << endl;
        tmxFile << "  <image source=\"data/tmx/floor.png\" width=\"" << tileSize << "\" height=\"" << tileSize << "\"/>" << endl;
        tmxFile << " </tileset>" << endl;
        tmxFile << " <tileset firstgid=\"2\" name=\"wall\" tilewidth=\"" << tileSize << "\" tileheight=\"" << tileSize << "\">" << endl;
        tmxFile << "  <image source=\"data/tmx/wall.png\" width=\"" << tileSize << "\" height=\"" << tileSize << "\"/>" << endl;
        tmxFile << " </tileset>" << endl;
        tmxFile << " <layer name=\"Tile Layer 1\" width=\"" << _size << "\" height=\"" << _size << "\">" << endl;
        tmxFile << "  <data>" << endl;

        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) {
                if (_map[i][j] == '@') {
                    // Add a wall tile.
                    tmxFile << "   <tile gid=\"2\"/>" << endl;
                } else {
                    // Add a floor tile.
                    tmxFile << "   <tile gid=\"1\"/>" << endl;
                }
            }
        }

        tmxFile << "  </data>" << endl;
        tmxFile << " </layer>" << endl;
        tmxFile << "</map>" << endl;
    } else {
        cerr << "Unable to open tmx file." << endl;
    }

    tmxFile.close();
}


/**
* Prints the room map.
*/
void Room::printMap() {
    cout << endl;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            cout << _map[i][j];
        }
        cout << endl;
    }
}


/**
* Creates a hall ending in a room with no other exits.
*/
void Room::_createDeadEnd() {
    int startEdge = 0;
    for (int i = 0; i < 4; ++i) {
        if (_exitBools[i] == true) {
            startEdge = i;
        }
    }

    int column = _getRand(1, _size - 5);
    int width = _getRand(column + 3, _size - 2);
    int row = _getRand(1, _size - 5);
    int height = _getRand(row + 3, _size - 2);
    int hall = 0;

    switch (startEdge) {
        case 0:
            // Top
            hall = _getRand(column, width);
            _top = hall;
            _drawHallCol(hall, 0, row);
            setEntrance(Vector2(hall, 0));
            break;
        case 1:
            // Right
            hall = _getRand(row, height);
            _right = hall;
            _drawHallRow(hall, width, _size);
            setEntrance(Vector2(_size - 2, hall));
            break;
        case 2:
            // Bottom
            hall = _getRand(column, width);
            _bottom = hall;
            _drawHallCol(hall, height, _size);
            setEntrance(Vector2(hall, _size - 2));
            break;
        case 3:
            // Left
            hall = _getRand(row, height);
            _left = hall;
            _drawHallRow(hall, 0, column);
            setEntrance(Vector2(1, hall));
            break;
        default:
            break;
    }

    _drawRoom(row, column, height, width);
}


/**
* Creates a straight hall.
*/
void Room::_createStraight() {
    int column = _getRand(1, _size - 2);
    int row = _getRand(1, _size - 2);

    if (_exitBools[0] && _exitBools[2]) {
        // up/down
        _top = column;
        _bottom = column;
        _drawHallCol(column, 0, _size);
        setEntrance(Vector2(column, _size - 2));

    } else if (_exitBools[1] && _exitBools[3]) {
        // left/right
        _right = row;
        _left = row;
        _drawHallRow(row, 0, _size);
        setEntrance(Vector2(1, row));
    }
}


/**
* Creates a hall with a single turn.
*/
void Room::_createTurn() {
    int column;
    int row;

    if (_exitBools[0] && _exitBools[1]) {
        // top/right
        column = _getRand(1, _size - 2);
        row = _getRand(column, _size - 2);
        _top = column;
        _right = row;

        _drawHallCol(column, 0, row + 1);
        _drawHallRow(row, column, _size);
        setEntrance(Vector2(column, 1));
    } else if (_exitBools[0] && _exitBools[3]) {
        // top/left
        column = _getRand(1, _size - 2);
        row = _getRand(1, column);
        _top = column;
        _left = row;

        _drawHallCol(column, 0, row + 1);
        _drawHallRow(row, 0, column);
        setEntrance(Vector2(column, 1));
    } else if (_exitBools[2] && _exitBools[1]) {
        // bottom/right
        column = _getRand(1, _size - 2);
        row = _getRand(column, _size - 2);
        _bottom = column;
        _right = row;

        _drawHallCol(column, row, _size);
        _drawHallRow(row, column, _size);
        setEntrance(Vector2(column, _size - 2));
    } else if (_exitBools[2] && _exitBools[3]) {
        // bottom/left
        column = _getRand(1, _size - 2);
        row = _getRand(1, column);
        _bottom = column;
        _left = row;

        _drawHallCol(column, row, _size);
        _drawHallRow(row, 0, column);
        setEntrance(Vector2(column, _size - 2));
    }
}


/**
* Creates a straight hall with a single branch.
*/
void Room::_createBranch() {
    int column = _getRand(1, _size - 2);
    int row = _getRand(1, _size - 2);

    if (_exitBools[0] && _exitBools[2]) {
        // up/down
        _top = column;
        _bottom = column;
        _drawHallCol(column, 0, _size);
        setEntrance(Vector2(column, _size - 2));
        row = _getRand(1, _size - 2);
        if (_exitBools[1]) {
            // right
            _right = row;
            _drawHallRow(row, column, _size);
        } else if (_exitBools[3]) {
            // left
            _left = row;
            _drawHallRow(row, 0, column);
        }
    } else if (_exitBools[1] && _exitBools[3]) {
        // right/left
        _right = row;
        _left = row;
        _drawHallRow(row, 0, _size);
        setEntrance(Vector2(1, row));
        column = _getRand(1, _size - 2);
        if (_exitBools[0]) {
            // up
            _top = column;
            _drawHallCol(column, 0, row);
        } else if (_exitBools[2]) {
            // down
            _bottom = column;
            _drawHallCol(column, row, _size);
        }
    }
}


/**
* Creates two intersecting straight halls.
*/
void Room::_createIntersection() {
    int column = _getRand(1, _size - 2);
    int row = _getRand(1, _size - 2);
    _top = column;
    _right = row;
    _bottom = column;
    _left = row;

    _drawHallCol(column, 0, _size);
    _drawHallRow(row, 0, _size);
    setEntrance(Vector2(column, _size - 2));
}


/**
* Adds all walls adjacent to map[i][j] to the wall list.
*
* @i is the i in map[i][j].
* @j is the j in map[i][j].
*/
void Room::_addWall(int i, int j) {
    bool onList = false;
    for (int k = 0; k < _wallListSize; ++k) {
        if (_wallList[k][0] == i && _wallList[k][1] == j) {
            onList = true;
            break;
        }
    }

    if (!onList && i != 0 && i != _size - 1 && j != 0 && j != _size - 1 && _map[i][j] == '@') {
        // Add wall
        _wallList[_wallListSize][0] = i;
        _wallList[_wallListSize][1] = j;
        _wallListSize++;
    }
}


/**
 * Chooses a random entrance, adds the first floor cell, and adds its walls to the wall list.
 *
 * @return the chosen edge.
 */
int Room::_chooseEntrance() {
    int edge = rand() % 3;
    int row = 0; // entrance row
    int col = 0; // entrance column
    if (edge == 0) {
        // Top
        // #x#
        // #.#
        // ###
        row = 0;
        col = rand() % (_size - 2) + 1;
        _map[row + 1][col] = '.';
        _map[row][col] = 'x';
        row++;

        // Add adjacent walls.
        _addWall(row + 1, col);
        _addWall(row, col + 1);
        _addWall(row, col - 1);
    } else if (edge == 1) {
        // Right
        // ###
        // #.x
        // ###
        row = rand() % (_size - 2) + 1;
        col = _size - 1;
        _map[row][col - 1] = '.';
        _map[row][col] = 'x';
        col--;

        // Add adjacent walls.
        _addWall(row - 1, col);
        _addWall(row + 1, col);
        _addWall(row, col - 1);
    } else if (edge == 2) {
        // Bottom
        // ###
        // #.#
        // #x#
        row = _size - 1;
        col = rand() % (_size - 2) + 1;
        _map[row - 1][col] = '.';
        _map[row][col] = 'x';
        row--;

        // Add adjacent walls.
        _addWall(row - 1, col);
        _addWall(row, col + 1);
        _addWall(row, col - 1);
    } else if (edge == 3) {
        // Left
        // ###
        // x.#
        // ###
        row = rand() % (_size - 2) + 1;
        col = 0;
        _map[row][col + 1] = '.';
        _map[row][col] = 'x';
        col++;

        // Add adjacent walls.
        _addWall(row - 1, col);
        _addWall(row + 1, col);
        _addWall(row, col + 1);
    }

    // Add the floor cell to the map list.
    _floorList[_floorListSize][0] = row;
    _floorList[_floorListSize][1] = col;
    _floorListSize++;

    // Set entrance.
    setEntrance(Vector2(col, row));

    return edge;
}


/**
* Choose a random map edge and cell for the exit.
*
* @edge is the entrance edge.
*/
int Room::_chooseExit(int edge) {
    int edgeList[3] = {0, 0, 0};
    if (edge == 0) {
        edgeList[0] = 1;
        edgeList[1] = 2;
        edgeList[2] = 3;
    } else if (edge == 1) {
        edgeList[0] = 0;
        edgeList[1] = 2;
        edgeList[2] = 3;
    } else if (edge == 2) {
        edgeList[0] = 0;
        edgeList[1] = 1;
        edgeList[2] = 3;
    } else if (edge == 3) {
        edgeList[0] = 0;
        edgeList[1] = 1;
        edgeList[2] = 2;
    }
    int index = rand() % 2;
    edge = edgeList[index];

    int i = 0;
    int j = 0;
    int temp = 0;
    int exitList[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int exitListSize = 0;
    if (edge == 0) {
        // Up
        i = 0;
        // j is random
        index = 1;
        for (int k = 1; k < _size - 2; ++k) {
            if (_map[index][k] == '.') {
                exitList[exitListSize] = k;
                exitListSize++;
            }
        }
        temp = rand() % exitListSize;
        j = exitList[temp];
    } else if (edge == 1) {
        // Right
        // i is random
        j = _size - 1;
        index = _size - 2;
        for (int k = 1; k < _size - 2; ++k) {
            if (_map[k][index] == '.') {
                exitList[exitListSize] = k;
                exitListSize++;
            }
        }
        temp = rand() % exitListSize;
        i = exitList[temp];
    } else if (edge == 2) {
        // Down
        i = _size - 1;
        // j is random
        index = _size - 2;
        for (int k = 1; k < _size - 2; ++k) {
            if (_map[index][k] == '.') {
                exitList[exitListSize] = k;
                exitListSize++;
            }
        }
        temp = rand() % exitListSize;
        j = exitList[temp];
    } else if (edge == 3) {
        // Left
        // i is random
        j = 0;
        index = _size - 2;
        for (int k = 1; k < _size - 2; ++k) {
            if (_map[k][index] == '.') {
                exitList[exitListSize] = k;
                exitListSize++;
            }
        }
        temp = rand() % exitListSize;
        i = exitList[temp];
    }

    // Create exit
    _map[i][j] = '.';

    return edge;
}


/**
* Returns a number between start and finish inclusive.
*
* @start is the beginning of the range.
* @finish is the end of the range, inclusive.
*/
int Room::_getRand(int start, int finish) {
    finish = finish - start + 1;
    return rand() % finish + start;
}


/**
* Draws a room between row and height, col and width.
*
* @row is the room's row index.
* @col is the room's column index.
* @height is the room's height index.
* @width is the room's width index.
*/
void Room::_drawRoom(int row, int col, int height, int width) {
    for (int i = row; i <= height; ++i) {
        for (int j = col; j <= width; ++j) {
            _map[i][j] = '.';
        }
    }
}


/**
* Draws a connecting hall on a column between a room and the main hall.
*
* @col is the hall's column index.
* @begin is the row index to begin on.
* @end is the row index to end on.
*/
void Room::_drawHallCol(int col, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        _map[i][col] = '.';
    }
}


/**
* Draws a connecting hall on a row between a room and the main hall.
*
* @row is the hall's row index.
* @begin is the column index to begin on.
* @end is the column index to end on.
*/
void Room::_drawHallRow(int row, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        _map[row][i] = '.';
    }
}


///**
//* Set map entrance.
//*
//* @entrance is the map location to set.
//*/
//void Room::_setEntrance(int row, int col) {
//    _entrance.x = col;
//    _entrance.y = row;
//}

///**
//* Creates a 2D map array using Prim's algorithm for minimum spanning trees.
//*/
//void Room::_createMaze() {
//    srand(static_cast<unsigned int>(time(0)));
//    int edge = _chooseEntrance();
//    int index = 0;
//    vector<int> wall;
//    int count = 0;
//
//    // While walls in wall list:
//    while (_wallListSize > 1) {
//        // Get a random wall from the list.
//        index = rand() % (_wallListSize - 1);
//        wall[0] = _wallList[index][0];
//        wall[1] = _wallList[index][1];
//
//        // Count adjacent cells already in the map.
//        count = 0;
//        for (int i = 0; i < _floorListSize; ++i) {
//            if ((_floorList[i][0] == wall[0] - 1 && _floorList[i][1] == wall[1]) ||
//                    (_floorList[i][0] == wall[0] && _floorList[i][1] == wall[1] + 1) ||
//                    (_floorList[i][0] == wall[0] + 1 && _floorList[i][1] == wall[1]) ||
//                    (_floorList[i][0] == wall[0] && _floorList[i][1] == wall[1] - 1)) {
//                count++;
//            }
//        }
//
//        int row = 0;
//        int col = 0;
//        // If only one of the adjacent cells is already in the map, continue.
//        if (count == 1) {
//            // Get the cell on the opposite side of the wall.
//            row = 0; // cell row
//            col = 0; // cell column
//            if (_map[wall[0] - 1][wall[1]] == '.') {
//                // Check up
//                // ###
//                // #r#
//                // #.#
//                row = wall[0] + 1;
//                col = wall[1];
//            } else if (_map[wall[0]][wall[1] + 1] == '.') {
//                // Check right
//                // ###
//                // .r#
//                // ###
//                row = wall[0];
//                col = wall[1] - 1;
//            } else if (_map[wall[0] + 1][wall[1]] == '.') {
//                // Check down
//                // #.#
//                // #r#
//                // ###
//                row = wall[0] - 1;
//                col = wall[1];
//            } else if (_map[wall[0]][wall[1] - 1] == '.') {
//                // Check left
//                // ###
//                // #r.
//                // ###
//                row = wall[0];
//                col = wall[1] + 1;
//            }
//
//            // Check if the cell on the opposite side of the chosen cell isn't in the map.
//            if (_map[row][col] == '@') {
//                // Make the chosen cell part of the map.
//                _map[wall[0]][wall[1]] = '.';
//
//                // Add it to the map list.
//                _floorList[_floorListSize][0] = wall[0];
//                _floorList[_floorListSize][1] = wall[1];
//                _floorListSize++;
//
//                // Add its walls.
//                _addWall(wall[0] - 1, wall[1]);
//                _addWall(wall[0], wall[1] + 1);
//                _addWall(wall[0] + 1, wall[1]);
//                _addWall(wall[0], wall[1] - 1);
//            }
//        }
//
//        // Remove the wall from the list.
//        for (int k = index; k < _wallListSize; ++k) {
//            _wallList[k][0] = _wallList[k + 1][0];
//            _wallList[k][1] = _wallList[k + 1][1];
//        }
//        _wallListSize--;
//    }
//
//    _chooseExit(edge);
//}
//
//
//
//
//
///**
//* Creates and draws a room on the map. Checks if the main hall is on a row or a column.
//* Then checks if there is space above or below a row and left or right of a column.
//* Connects the room(s) to the main hall with connecting halls.
//*/
//void Room::_createHallMap(int exits) {
//    // If not coming from another room use the same method to choose the starting location,
//    // else choose the same wall as the last room's exit.
//    // TODO change entrance location for branch vs split
//    // split starts on the hall leading to the T
//    // branch starts on the straight hall with the branch off the side
//
////    int startEdge = _chooseEntrance();
//
//    // edges: top 0, right 1, down 2, left 3
//    int startEdge = 0;
//    int row = 0;
//    int col = 0;
//    int column = false;
//
//    if (_exitBools[0] == true && _exitBools[2] == true) {
//        // Top/down main hall
//        startEdge = 2;
//        row = _getRand(1, _size - 2);
//        col = _size - 1;
//        column = true;
//
//    } else if (_exitBools[1] == true && _exitBools[2] == true) {
//        // Left/Right main hall
//        startEdge = 1;
//        row = 1;
//        col = _getRand(1, _size - 2);
//    }
//
//    setEntrance(Vector2(col, row));
//
//    // Decide direction for adding new cells.
//    int x = 0;
//    int y = 0;
//    switch (startEdge) {
//        case 0:
//            // Top
//            x = 1;
//            column = true;
//            break;
//        case 1:
//            // Right
//            y = -1;
//            break;
//        case 2:
//            // Bottom
//            x = -1;
//            column = true;
//            break;
//        case 3:
//            // Left
//            y = 1;
//            break;
//        default:
//            break;
//    }
//
//    // Draw the hall.
//    while (!_atExit(row, col)) {
//        row += x;
//        col += y;
//        _map[row][col] = '.';
//    }
//
//    int randCol = 0;
//    int randRow = 0;
//    int randWidth = 0;
//    int randHeight = 0;
//
//    // Draw the rooms.
//    if (column) {
//        int connectHallRow = 0;
//        if (col > 3) {
//            // Left of hall
//
//            // between 1 and col - 3
//            randCol = _getRand(1, col - 2);
//            // between randCol + 1 and col - 1
//            randWidth = _getRand(randCol + 1, col - 1);
//
//            // between 1 and _size - 3
//            randRow = _getRand(1, _size - 3);
//            // between randRow + 1 and _size - 2
//            randHeight = _getRand(randRow + 1, _size - 2);
//
//            _drawRoom(randRow, randCol, randHeight, randWidth);
//
//            connectHallRow = _getRand(randRow, randHeight);
//
//            // draw connecting hall on connectHallRow from randWidth + 1 to col
//            _drawHallRow(connectHallRow, randWidth + 1, col);
//        }
//        if (col < _size - 4) {
//            // Right of hall
//
//            // between col + 1 and _size - 2
//            randCol = _getRand(col + 1, _size - 3);
//            // between randCol + 1 and _size - 2
//            randWidth = _getRand(randCol + 1, _size - 2);
//
//            // between 1 and _size - 2
//            randRow = _getRand(1, _size - 3);
//            // between randRow + 1 and _size - 2
//            randHeight = _getRand(randRow + 1, _size - 2);
//
//            _drawRoom(randRow, randCol, randHeight, randWidth);
//
//            connectHallRow = _getRand(randRow, randHeight);
//
//            // draw connecting hall on connectHallRow from col + 1 to randCol
//            _drawHallRow(connectHallRow, col + 1, randCol);
//        }
//        if (exits > 1) {
//            int exitRow = _getRand(1, _size - 2);
//            if (_exitBools[1] == true) {
//                // go right
//                _drawHallRow(exitRow, col, _size);
//            }
//            exitRow = _getRand(1, _size - 2);
//            if (_exitBools[3] == true) {
//                // go left
//                _drawHallRow(exitRow, 0, col);
//            }
//        }
//    } else { // if row
//        int connectHallCol = 0;
//        if (row > 3) {
//            // Above hall
//
//            // between 1 and row - 1
//            randRow = _getRand(1, row - 2);
//            // between randRow + 1 and row - 1
//            randHeight = _getRand(randRow + 1, row - 1);
//
//            // between 1 and _size - 2
//            randCol = _getRand(1, _size - 3);
//            // between randCol + 1 and _size - 2
//            randWidth = _getRand(randCol + 1, _size - 2);
//
//            _drawRoom(randRow, randCol, randHeight, randWidth);
//
//            connectHallCol = _getRand(randCol, randWidth);
//
//            // draw connecting hall on connectHallCol from randHeight + 1 to row
//            _drawHallCol(connectHallCol, randHeight + 1, row);
//        }
//        if (row < _size - 4) {
//            // Below hall
//
//            // between 1 and _size - 3
//            randCol = _getRand(row + 1, _size - 3);
//            // between randCol + 1 and _size - 2
//            randWidth = _getRand(randCol + 1, _size - 2);
//
//            // between row + 1 and _size - 3
//            randRow = _getRand(row + 1, _size - 3);
//            // between randRow + 1 and _size - 2
//            randHeight = _getRand(randRow + 1, _size - 2);
//
//            _drawRoom(randRow, randCol, randHeight, randWidth);
//
//            connectHallCol = _getRand(randCol, randWidth);
//
//            // draw connecting hall on connectHallCol from row + 1 to randRow
//            _drawHallCol(connectHallCol, row + 1, randRow);
//        }
//        if (exits > 1) {
//            int exitCol = _getRand(1, _size - 2);
//            if (_exitBools[0] == true) {
//                // go up
//                _drawHallCol(exitCol, 0, row);
//            }
//            exitCol = _getRand(1, _size - 2);
//            if (_exitBools[2] == true) {
//                // go down
//                _drawHallCol(exitCol, row, _size);
//            }
//        }
//    }
//}
