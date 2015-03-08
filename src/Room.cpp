#include <iostream>
#include <fstream>
#include <random>
#include "Room.h"
#include "Chest.h"

#include "Bat.h"
#include "Snake.h"
#include "Ghost.h"
#include "Eyeball.h"
#include "Worm.h"
#include "Slime.h"


using namespace std;

enum RoomType {deadend, straight, turn, branch, intersection, outsideTop, outsideRight, outsideBottom, outsideLeft};

Room::Room() {}

Room::Room(int type, int size, vector<bool> exitBools):
           _type(type), _size(size), _wallListSize(0), _floorListSize(0),
           _top(0), _right(0), _bottom(0), _left(0), _exitBools(exitBools) {
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
        case outsideTop:
            setEntrance(Vector2(6, _size - 2));
            _bottom = 6;
            break;
        case outsideRight:
            setEntrance(Vector2(1, 6));
            _left = 6;
            break;
        case outsideBottom:
            setEntrance(Vector2(6, 1));
            _top = 6;
            break;
        case outsideLeft:
            setEntrance(Vector2(_size - 2, 6));
            _right = 6;
            break;
        default:
            break;
    }
//    printMap();
}


/**
* Creates a tile map (.tmx file) from the 2D map array.
*/
void Room::createTileMap(string file) {
    if (_type != outsideTop && _type != outsideRight && _type != outsideBottom && _type != outsideLeft) {
        ofstream tmxFile;
        tmxFile.open("tmx/room.tmx");

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
    } else {
        _createOutsideTileMap(file);
    }
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


int Room::getSize() const {
    return _size;
}

void Room::setSize(int size) {
    _size = size;
}

Vector2 Room::getEntrance() {
    return _entrance;
}

void Room::setEntrance(Vector2 entrance) {
    _entrance = entrance;
}

vector<SDL_Rect> Room::getTiles() {
    return _tiles;
}

void Room::setTiles(vector<SDL_Rect> tiles) {
    _tiles = tiles;
}

list<spUnit>* Room::getUnits() {
    return &_units;
}

int Room::getType() {
    return _type;
}

vector<Vector2> Room::getExits() {
    return _exits;
}

void Room::setExits(vector<Vector2> exits) {
    _exits = exits;
}

int Room::getTop() {
    return _top;
}

void Room::setTop(int top) {
    _top = top;
}

int Room::getRight() {
    return _right;
}

void Room::setRight(int right) {
    _right = right;
}

int Room::getBottom() {
    return _bottom;
}

void Room::setBottom(int bottom) {
    _bottom = bottom;
}

int Room::getLeft() {
    return _left;
}

void Room::setLeft(int left) {
    _left = left;
}


/**
*  Copies one of the outside tile maps (.tmx) to room.tmx.
*/
void Room::_createOutsideTileMap(string tmxFile) {
    ifstream source(tmxFile, ios::binary);
    ofstream destination("tmx/room.tmx", ios::binary);

    destination << source.rdbuf();

    source.close();
    destination.close();
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
    bool isColumn = false;

    switch (startEdge) {
        case 0:
            // Top
            isColumn = true;
            hall = _getRand(column, width);
            _top = hall;
            _drawHallCol(hall, 0, row);
            setEntrance(Vector2(hall, 1));
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
            isColumn = true;
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
    _drawOpenSpaces(row, column, true);
}


/**
* Creates a straight hall.
*/
void Room::_createStraight() {
    int column = _getRand(1, _size - 2);
    int row = _getRand(1, _size - 2);
    bool isColumn = false;
    
    // Create main hall
    if (_exitBools[0] && _exitBools[2]) {
        // up/down
        isColumn = true;
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
    
    _drawOpenSpaces(row, column, isColumn);
}


/**
* Creates a hall with a single turn.
*/
void Room::_createTurn() {
    int column = 0;
    int row = 0;

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
    
    _drawOpenSpaces(row, column, true);
    _drawOpenSpaces(row, column, false);
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
    
    _drawOpenSpaces(row, column, true);
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
    
    _drawOpenSpaces(row, column, true);
    _drawOpenSpaces(row, column, false);
}


/**
* Creates an empty room.
*/
void Room::_createEmpty() {
    for (int i = 0; i < _size - 1; ++i) {
        for (int j = 0; j < _size - 1; ++j) {
            _map[i][j] = '.';
        }
    }
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
 * Draws open spaces in the room.
 *
 * @row
 * @column
 * @isColumn
 */
void Room::_drawOpenSpaces(int row, int column, bool isColumn) {
    int roomCol = _getRand(1, _size / 2);
    int roomWidth = _getRand(roomCol, _size - 2);
    int roomRow = _getRand(1, _size / 2);
    int roomHeight = _getRand(roomRow, _size - 2);
    
    // Draw the rooms.
    if (isColumn) {
        int connectHallRow = 0;
        if (column > 3) {
            // Left of hall
            
            // between 1 and col - 3
            roomCol = _getRand(1, column - 2);
            // between randCol + 1 and col - 1
            roomWidth = _getRand(roomCol + 1, column - 1);
            
            // between 1 and _size - 3
            roomRow = _getRand(1, _size - 3);
            // between randRow + 1 and _size - 2
            roomHeight = _getRand(roomRow + 1, _size - 2);
            
            _drawRoom(roomRow, roomCol, roomHeight, roomWidth);
            
            connectHallRow = _getRand(roomRow, roomHeight);
            
            // draw connecting hall on connectHallRow from randWidth + 1 to col
            _drawHallRow(connectHallRow, roomWidth + 1, column);
        }
        if (column < _size - 4) {
            // Right of hall
            
            // between col + 1 and _size - 2
            roomCol = _getRand(column + 1, _size - 3);
            // between randCol + 1 and _size - 2
            roomWidth = _getRand(roomCol + 1, _size - 2);
            
            // between 1 and _size - 2
            roomRow = _getRand(1, _size - 3);
            // between randRow + 1 and _size - 2
            roomHeight = _getRand(roomRow + 1, _size - 2);
            
            _drawRoom(roomRow, roomCol, roomHeight, roomWidth);
            
            connectHallRow = _getRand(roomRow, roomHeight);
            
            // draw connecting hall on connectHallRow from col + 1 to randCol
            _drawHallRow(connectHallRow, column + 1, roomCol);
        }
    } else { // if row
        int connectHallCol = 0;
        if (row > 3) {
            // Above hall
            
            // between 1 and row - 1
            roomRow = _getRand(1, row - 2);
            // between randRow + 1 and row - 1
            roomHeight = _getRand(roomRow + 1, row - 1);
            
            // between 1 and _size - 2
            roomCol = _getRand(1, _size - 3);
            // between randCol + 1 and _size - 2
            roomWidth = _getRand(roomCol + 1, _size - 2);
            
            _drawRoom(roomRow, roomCol, roomHeight, roomWidth);
            
            connectHallCol = _getRand(roomCol, roomWidth);
            
            // draw connecting hall on connectHallCol from randHeight + 1 to row
            _drawHallCol(connectHallCol, roomHeight + 1, row);
        }
        if (row < _size - 4) {
            // Below hall
            
            // between 1 and _size - 3
            roomCol = _getRand(row + 1, _size - 3);
            // between randCol + 1 and _size - 2
            roomWidth = _getRand(roomCol + 1, _size - 2);
            
            // between row + 1 and _size - 3
            roomRow = _getRand(row + 1, _size - 3);
            // between randRow + 1 and _size - 2
            roomHeight = _getRand(roomRow + 1, _size - 2);
            
            _drawRoom(roomRow, roomCol, roomHeight, roomWidth);
            
            connectHallCol = _getRand(roomCol, roomWidth);
            // draw connecting hall on connectHallCol from row + 1 to randRow
            _drawHallCol(connectHallCol, row + 1, roomRow);
        }
    }
    
    // Create a chest 1/3 of the time
    int randChoice = 0;
    //_getRand(0, 2);
    if (randChoice == 0) {
        int chestRow = _getRand(roomRow, roomHeight) * 64;
        int chestCol = _getRand(roomCol, roomWidth) * 64;
        spChest chest = new Chest;
        chest->setLocation(Vector2(chestCol, chestRow));
        _units.push_back(chest);
    }

    if(_units.size() < 3) {
        int numOfSmall = _getRand(3, 6);
        for (int i = 0; i < numOfSmall; i++) {
            int rand = _getRand(1, 3);
            int randRow = _getRand(roomRow, roomHeight) * 64;
            int randCol = _getRand(roomCol, roomWidth) * 64;

            if (rand == 1) {
                spBat bat = new Bat;
                bat->setLocation(Vector2(randCol, randRow));
                _units.push_back(bat);
            } else if (rand == 2) {
                spSnake snake = new Snake;
                snake->setLocation(Vector2(randCol, randRow));
                _units.push_back(snake);
            } else if (rand == 3) {
                spSlime slime = new Slime;
                slime->setLocation(Vector2(randCol, randRow));
                _units.push_back(slime);
            }
        }

        int numOfLarge = _getRand(1, 2);
        for (int i = 0; i < numOfLarge; i++) {
            int rand = _getRand(1, 3);
            int randRow = _getRand(roomRow, roomHeight) * 64;
            int randCol = _getRand(roomCol, roomWidth) * 64;

            if (rand == 1) {
                spWorm worm = new Worm;
                worm->setLocation(Vector2(randCol, randRow));
                _units.push_back(worm);
            } else if (rand == 2) {
                spEyeball eyeball = new Eyeball;
                eyeball->setLocation(Vector2(randCol, randRow));
                _units.push_back(eyeball);
            } else if (rand == 3) {
                spGhost ghost = new Ghost;
                ghost->setLocation(Vector2(randCol, randRow));
                _units.push_back(ghost);
            }
        }
    }
    
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