#include <iostream>
#include <fstream>
#include "Map.h"
using namespace std;


/**
 * Constructor.
 */
Map::Map(int size):_size(size), _wallListSize(0), _mazeListSize(0) {
    // Seed rand.
    srand((unsigned int) time(NULL));
    
    // Initialize the maze.
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _maze[i][j] = '@';
        }
    }
    
    // Initialize the lists.
    for (int i = 0; i < _maxListSize; ++i) {
        _wallList[i][0] = 0;
        _wallList[i][1] = 0;
        
        _mazeList[i][0] = 0;
        _mazeList[i][1] = 0;
    }
    
    _entrance = Vector2();
}


/**
 * Get map entrance.
 */
Vector2 Map::getEntrance() {
    return _entrance;
}


/**
 * Set map entrance.
 *
 * @entrance is the map location to set.
 */
void Map::setEntrance(int x, int y) {
    _entrance.x = y;
    _entrance.y = x;
}


/**
 * Adds all walls adjacent to maze[i][j] to the wall list.
 *
 * @i is the i in maze[i][j].
 * @j is the j in maze[i][j].
 */
void Map::_addWall(int i, int j) {
    bool onList = false;
    for (int k = 0; k < _wallListSize; ++k) {
        if (_wallList[k][0] == i && _wallList[k][1] == j) {
            onList = true;
            break;
        }
    }
    
    if (!onList && i != 0 && i != _size - 1 && j != 0 && j != _size - 1 && _maze[i][j] == '@') {
        // Add wall
        _wallList[_wallListSize][0] = i;
        _wallList[_wallListSize][1] = j;
        _wallListSize++;
    }
}


/**
 * Randomly chooses an entrance, adds the first floor cell, and adds its walls to the wall list.
 *
 * @return the chosen edge.
 */
int Map::_chooseEntrance() {
    int edge = rand() % 3;
    int a = 0; // entrance row
    int b = 0; // entrance column
    if (edge == 0) {
        // Top
        // #x#
        // #.#
        // ###
        a = 0;
        b = rand() % (_size - 2) + 1;
        _maze[a + 1][b] = '.';
        _maze[a][b] = 'x';
        a++;
        
        // Add adjacent walls.
        _addWall(a + 1, b);
        _addWall(a, b + 1);
        _addWall(a, b - 1);
    } else if (edge == 1) {
        // Right
        // ###
        // #.x
        // ###
        a = rand() % (_size - 2) + 1;
        b = _size - 1;
        _maze[a][b - 1] = '.';
        _maze[a][b] = 'x';
        b--;
        
        // Add adjacent walls.
        _addWall(a - 1, b);
        _addWall(a + 1, b);
        _addWall(a, b - 1);
    } else if (edge == 2) {
        // Bottom
        // ###
        // #.#
        // #x#
        a = _size - 1;
        b = rand() % (_size - 2) + 1;
        _maze[a - 1][b] = '.';
        _maze[a][b] = 'x';
        a--;
        
        // Add adjacent walls.
        _addWall(a - 1, b);
        _addWall(a, b + 1);
        _addWall(a, b - 1);
    } else if (edge == 3) {
        // Left
        // ###
        // x.#
        // ###
        a = rand() % (_size - 2) + 1;
        b = 0;
        _maze[a][b + 1] = '.';
        _maze[a][b] = 'x';
        b++;
        
        // Add adjacent walls.
        _addWall(a - 1, b);
        _addWall(a + 1, b);
        _addWall(a, b + 1);
    }
    
    // Add the floor cell to the maze list.
    _mazeList[_mazeListSize][0] = a;
    _mazeList[_mazeListSize][1] = b;
    _mazeListSize++;
    
    // Set entrance.
    setEntrance(a, b);
    
    return edge;
}


/**
 * Choose a random maze edge and cell for the exit.
 *
 * @edge is the entrance edge.
 */
int Map::_chooseExit(int edge) {
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
    index = 0;
    int exitList[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int exitListSize = 0;
    if (edge == 0) {
        // Up
        i = 0;
        // j is random
        index = 1;
        for (int k = 1; k < _size - 2; ++k) {
            if (_maze[index][k] == '.') {
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
            if (_maze[k][index] == '.') {
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
            if (_maze[index][k] == '.') {
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
            if (_maze[k][index] == '.') {
                exitList[exitListSize] = k;
                exitListSize++;
            }
        }
        temp = rand() % exitListSize;
        i = exitList[temp];
    }
    
    // Create exit
    _maze[i][j] = '.';
    
    return edge;
}


/**
 * Creates a 2D maze array using Prim's algorithm for minimum spanning trees.
 */
void Map::createMaze() {
    int edge = _chooseEntrance();
    
    int index = 0;
    int wall[2] = {0, 0};
    int n = 0;
    int m = 0;
    int count = 0;
    
    // While walls in wall list:
    while (_wallListSize > 1) {
        // Get a random wall from the list.
        index = rand() % (_wallListSize - 1);
        wall[0] = _wallList[index][0];
        wall[1] = _wallList[index][1];
        
        // Count adjacent cells already in the maze.
        count = 0;
        for (int i = 0; i < _mazeListSize; ++i) {
            if ((_mazeList[i][0] == wall[0] - 1 && _mazeList[i][1] == wall[1]) ||
                (_mazeList[i][0] == wall[0] && _mazeList[i][1] == wall[1] + 1) ||
                (_mazeList[i][0] == wall[0] + 1 && _mazeList[i][1] == wall[1]) ||
                (_mazeList[i][0] == wall[0] && _mazeList[i][1] == wall[1] - 1)) {
                count++;
            }
        }
        
        // If only one of the adjacent cells is already in the maze, continue.
        if (count == 1) {
            // Get the cell on the opposite side of the wall.
            n = 0; // cell row
            m = 0; // cell column
            if (_maze[wall[0] - 1][wall[1]] == '.') {
                // Check up
                // ###
                // #r#
                // #.#
                n = wall[0] + 1;
                m = wall[1];
            } else if (_maze[wall[0]][wall[1] + 1] == '.') {
                // Check right
                // ###
                // .r#
                // ###
                n = wall[0];
                m = wall[1] - 1;
            } else if (_maze[wall[0] + 1][wall[1]] == '.') {
                // Check down
                // #.#
                // #r#
                // ###
                n = wall[0] - 1;
                m = wall[1];
            } else if (_maze[wall[0]][wall[1] - 1] == '.') {
                // Check left
                // ###
                // #r.
                // ###
                n = wall[0];
                m = wall[1] + 1;
            }
            
            // Check if the cell on the opposite side of the chosen cell isn't in the maze.
            if (_maze[n][m] == '@') {
                // Make the chosen cell part of the maze.
                _maze[wall[0]][wall[1]] = '.';
                
                // Add it to the maze list.
                _mazeList[_mazeListSize][0] = wall[0];
                _mazeList[_mazeListSize][1] = wall[1];
                _mazeListSize++;
                
                // Add its walls.
                _addWall(wall[0] - 1, wall[1]);
                _addWall(wall[0], wall[1] + 1);
                _addWall(wall[0] + 1, wall[1]);
                _addWall(wall[0], wall[1] - 1);
            }
        }
        
        // Remove the wall from the list.
        for (int k = index; k < _wallListSize; ++k) {
            _wallList[k][0] = _wallList[k + 1][0];
            _wallList[k][1] = _wallList[k + 1][1];
        }
        _wallListSize--;
    }
    
    _chooseExit(edge);
    
    _createTileMap();
}


/**
 * Return true if the maze exit has been reached, otherwise false.
 *
 * @row is the row to check.
 * @col is the col to check.
 */
bool Map::_atExit(int row, int col) {
    return row == 0 || row == _size - 1 || col == 0 || col == _size - 1;
}


/**
 * Returns a number betweeen start and finish inclusive.
 *
 * @start is the beginning of the range.
 * @finish is the end of the range, inclusive.
 */
int Map::_getRand(int start, int finish) {
    finish = finish - start + 1;
    return rand() % finish + start;
}


void Map::_drawRoom(int row, int col, int height, int width) {
    
    std::printf("row: %d\n", row);
    std::printf("col: %d\n", col);
    std::printf("height: %d\n", height);
    std::printf("width: %d\n", width);
    
    for (int i = row; i <= height; ++i) {
        for (int j = col; j <= width; ++j) {
            std::printf("i: %d, j: %d\n", i, j);
            _maze[i][j] = '.';
        }
    }
}


void Map::_drawConnectHallCol(int col, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        _maze[i][col] = '.';
    }
}


void Map::_drawConnectHallRow(int row, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        _maze[row][i] = '.';
    }
}


void Map::createRoom() {
    // If not coming from another room use the same method to choose the starting location,
    // else choose the same wall as the last room's exit.
    
    int startEdge = _chooseEntrance();
    Vector2 location = getEntrance();
    int col = location.x;
    int row = location.y;
    int x = 0;
    int y = 0;
    bool column = false;
    
    std::printf("row: %d, col: %d\n", row, col);
    
    // Decide movement direction for adding new cells.
    // #0#
    // 3#1
    // #2#
    switch (startEdge) {
        case 0:
            // Top
            x = 1;
            column = true;
            break;
        case 1:
            // Right
            y = -1;
            break;
        case 2:
            // Bottom
            x = -1;
            column = true;
            break;
        case 3:
            // Left
            y = 1;
            break;
        default:
            break;
    }
    
    // Draw the hall.
    while (!_atExit(row, col)) {
        row += x;
        col += y;
        _maze[row][col] = '.';
    }
    
    int randCol = 0;
    int randRow = 0;
    int randWidth = 0;
    int randHeight = 0;
    
    // Draw the rooms.
    if (column) {
        int connectHallRow = 0;
        if (col > 3) {
            // Left of hall
            std::printf("Left of hall\n");
            
            // between 1 and col - 3
            randCol = _getRand(1, col - 2);
            // between randCol + 1 and col - 1
            randWidth = _getRand(randCol + 1, col - 1);
            
            // between 1 and _size - 3
            randRow = _getRand(1, _size - 3);
            // between randRow + 1 and _size - 2
            randHeight = _getRand(randRow + 1, _size - 2);
            
            _drawRoom(randRow, randCol, randHeight, randWidth);
            
            connectHallRow = _getRand(randRow, randHeight);
            
            // draw connecting hall on connectHallRow from randWidth + 1 to col
            _drawConnectHallRow(connectHallRow, randWidth + 1, col);
        }
        if (col < _size - 4) {
            // Right of hall
            std::printf("Right of hall\n");
            
            // between col + 1 and _size - 2
            randCol = _getRand(col + 1, _size - 3);
            // between randCol + 1 and _size - 2
            randWidth = _getRand(randCol + 1, _size - 2);
            
            // between 1 and _size - 2
            randRow = _getRand(1, _size - 3);
            // between randRow + 1 and _size - 2
            randHeight = _getRand(randRow + 1, _size - 2);
            
            _drawRoom(randRow, randCol, randHeight, randWidth);
            
            connectHallRow = _getRand(randRow, randHeight);
            
            // draw connecting hall on connectHallRow from col + 1 to randCol
            _drawConnectHallRow(connectHallRow, col + 1, randCol);
        }
    } else { // if row
        int connectHallCol = 0;
        if (row > 3) {
            // Above hall
            std::printf("Above hall\n");
            
            // between 1 and row - 1
            randRow = _getRand(1, row - 2);
            // between randRow + 1 and row - 1
            randHeight = _getRand(randRow + 1, row - 1);

            // between 1 and _size - 2
            randCol = _getRand(1, _size - 3);
            // between randCol + 1 and _size - 2
            randWidth = _getRand(randCol + 1, _size - 2);
            
            _drawRoom(randRow, randCol, randHeight, randWidth);
            
            connectHallCol = _getRand(randCol, randWidth);
            
            // draw connecting hall on connectHallCol from randHeight + 1 to row
            _drawConnectHallCol(connectHallCol, randHeight + 1, row);
        }
        if (row < _size - 4) {
            // Below hall
            std::printf("Below hall\n");
            
            // between 1 and _size - 3
            randCol = _getRand(row + 1, _size - 3);
            // between randCol + 1 and _size - 2
            randWidth = _getRand(randCol + 1, _size - 2);
            
            // between row + 1 and _size - 3
            randRow = _getRand(row + 1, _size - 3);
            // between randRow + 1 and _size - 2
            randHeight = _getRand(randRow + 1, _size - 2);
            
            _drawRoom(randRow, randCol, randHeight, randWidth);
            
            connectHallCol = _getRand(randCol, randWidth);
            
            // draw connecting hall on connectHallCol from row + 1 to randRow
            _drawConnectHallCol(connectHallCol, row + 1, randRow);
        }
    }
    
    
    
    
    
    
//    int endEdge = _chooseExit(startEdge);
//    
////    randomly decide the number and position of exits
//    int exists = rand() % 3;
////    randomly decide if there are going to be turns in the hall
//    int turns = rand() % 3;
//
//    if (turns > 0) {
//        int start = 1;
//        int end = _size / 2;
//        for (int i = 0; i < turns; ++i) {
//            // Determine spacing between turns choose random number between start and end
//            int space = start + (rand() % end);
//            // add cells from entrance to first turn
//            int direction = rand() % 2;
//            if (direction == 0) {
//                // turn left
//            } else {
//                // turn right
//            }
//            // randomly choose a number of cells before the turn between 2 and a max size based on room size
//        }
//    }
//    connect hallway to the other end of the map
//    connect the exists to the hallway
//    randomly decide how many rooms will be off to the side of the hall based on the amount of available space
//    create a door to each room
//    randomly decide how large the rooms will be with max size being the available space
//    draw the rooms
    
    _createTileMap();
    printMaze();
}


/**
 * Prints the maze.
 */
void Map::printMaze() {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            cout << _maze[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


/**
 * Creates a tile map (.tmx file) from the 2D maze array.
 */
void Map::_createTileMap() {
    ofstream tmxFile;
    tmxFile.open("data/tmx/room.tmx");
    
    if (tmxFile.is_open()) {
        tmxFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        tmxFile << "<map version=\"1.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"" << _size << "\" height=\"" << _size << "\" tilewidth=\"32\" tileheight=\"32\" nextobjectid=\"1\">" << endl;
        tmxFile << " <tileset firstgid=\"1\" name=\"floor\" tilewidth=\"32\" tileheight=\"32\">" << endl;
        tmxFile << "  <image source=\"data/tmx/floor.png\" width=\"32\" height=\"32\"/>" << endl;
        tmxFile << " </tileset>" << endl;
        tmxFile << " <tileset firstgid=\"2\" name=\"wall\" tilewidth=\"32\" tileheight=\"32\">" << endl;
        tmxFile << "  <image source=\"data/tmx/wall.png\" width=\"32\" height=\"32\"/>" << endl;
        tmxFile << " </tileset>" << endl;
        tmxFile << " <layer name=\"Tile Layer 1\" width=\"" << _size << "\" height=\"" << _size << "\">" << endl;
        tmxFile << "  <data>" << endl;
        
        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) {
                if (_maze[i][j] == '@') {
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


///**
// * Constructor.
// */
//Map::Map(int size):size(size) {
//    maze = vector<vector<char>>();
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            maze[i][j] = '@';
//        }
//    }
//    
//    walls = vector<vector<int>>();
//    mazeList = vector<vector<int>>();
//    
//    createMaze();
//    printMaze();
//}
//
//
///**
// * Adds all walls to list that are adjacent to maze[i][j].
// *
// * @i is the i in maze[i][j].
// * @j is the j in maze[i][j].
// */
//void Map::_addWall(int i, int j) {
//    bool onList = false;
//    for (int k = 0; k < size; ++k) {
//        if (walls[k][0] == i && walls[k][1] == j) {
//            onList = true;
//            break;
//        }
//    }
//    
//    if (!onList && i != 0 && i != size - 1 && j != 0 && j != size - 1 && maze[i][j] == '@') {
//        // Add wall
//        walls.push_back({i, j});
//    }
//}
//
//
///**
// * Creates a 2D maze vector using Prim's algorithm for minimum spanning trees.
// */
//void Map::createMaze() {
//    // Randomly choose an entrance, add the first floor cell, and add its walls to the wall list.
//    int edge = rand() % 3;
//    int a = 0; // entrance row
//    int b = 0; // entrance column
//    if (edge == 0) {
//        // Top
//        // #x#
//        // #.#
//        // ###
//        a = 0;
//        b = rand() % (size - 2) + 1;
//        maze[a + 1][b] = '.';
//        maze[a][b] = 'x';
//        a++;
//        
//        // Add adjacent walls.
//        _addWall(a + 1, b);
//        _addWall(a, b + 1);
//        _addWall(a, b - 1);
//    } else if (edge == 1) {
//        // Right
//        // ###
//        // #.x
//        // ###
//        a = rand() % (size - 2) + 1;
//        b = size - 1;
//        maze[a][b - 1] = '.';
//        maze[a][b] = 'x';
//        b--;
//        
//        // Add adjacent walls.
//        _addWall(a - 1, b);
//        _addWall(a + 1, b);
//        _addWall(a, b - 1);
//    } else if (edge == 2) {
//        // Bottom
//        // ###
//        // #.#
//        // #x#
//        a = size - 1;
//        b = rand() % (size - 2) + 1;
//        maze[a - 1][b] = '.';
//        maze[a][b] = 'x';
//        a--;
//        
//        // Add adjacent walls.
//        _addWall(a - 1, b);
//        _addWall(a, b + 1);
//        _addWall(a, b - 1);
//    } else if (edge == 3) {
//        // Left
//        // ###
//        // x.#
//        // ###
//        a = rand() % (size - 2) + 1;
//        b = 0;
//        maze[a][b + 1] = '.';
//        maze[a][b] = 'x';
//        b++;
//        
//        // Add adjacent walls.
//        _addWall(a - 1, b);
//        _addWall(a + 1, b);
//        _addWall(a, b + 1);
//    }
//    
//    // Add the floor cell to the maze list.
//    mazeList.push_back({a, b});
//    
//    int index = 0;
//    int wall[2] = {0, 0};
//    int n = 0;
//    int m = 0;
//    int count = 0;
//    
//    // While walls in wall list:
//    while (walls.size() > 1) {
//        // Get a random wall from the list.
//        index = rand() % (walls.size() - 1);
//        wall[0] = walls[index][0];
//        wall[1] = walls[index][1];
//        
//        // Count adjacent cells already in the maze.
//        count = 0;
//        size_t mazeListSize = mazeList.size();
//        for (int i = 0; i < mazeListSize; ++i) {
//            if ((mazeList[i][0] == wall[0] - 1 && mazeList[i][1] == wall[1]) ||
//                (mazeList[i][0] == wall[0] && mazeList[i][1] == wall[1] + 1) ||
//                (mazeList[i][0] == wall[0] + 1 && mazeList[i][1] == wall[1]) ||
//                (mazeList[i][0] == wall[0] && mazeList[i][1] == wall[1] - 1)) {
//                count++;
//            }
//        }
//        
//        // If only one of the adjacent cells is already in the maze, continue.
//        if (count == 1) {
//            // Get the cell on the opposite side of the wall.
//            n = 0; // cell row
//            m = 0; // cell column
//            if (maze[wall[0] - 1][wall[1]] == '.') {
//                // Check up
//                // ###
//                // #r#
//                // #.#
//                n = wall[0] + 1;
//                m = wall[1];
//            } else if (maze[wall[0]][wall[1] + 1] == '.') {
//                // Check right
//                // ###
//                // .r#
//                // ###
//                n = wall[0];
//                m = wall[1] - 1;
//            } else if (maze[wall[0] + 1][wall[1]] == '.') {
//                // Check down
//                // #.#
//                // #r#
//                // ###
//                n = wall[0] - 1;
//                m = wall[1];
//            } else if (maze[wall[0]][wall[1] - 1] == '.') {
//                // Check left
//                // ###
//                // #r.
//                // ###
//                n = wall[0];
//                m = wall[1] + 1;
//            }
//            
//            // Check if the cell on the opposite side of the chosen cell isn't in the maze.
//            if (maze[n][m] == '@') {
//                // Make the chosen cell part of the maze.
//                maze[wall[0]][wall[1]] = '.';
//                
//                // Add it to the maze list.
//                mazeList.push_back({wall[0], wall[1]});
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
//        walls.erase(walls.begin() + index);
//    }
//    
//    // Choose random maze edge for the exit.
//    int edgeList[3] = {0, 0, 0};
//    if (edge == 0) {
//        edgeList[0] = 1;
//        edgeList[1] = 2;
//        edgeList[2] = 3;
//    } else if (edge == 1) {
//        edgeList[0] = 0;
//        edgeList[1] = 2;
//        edgeList[2] = 3;
//    } else if (edge == 2) {
//        edgeList[0] = 0;
//        edgeList[1] = 1;
//        edgeList[2] = 3;
//    } else if (edge == 3) {
//        edgeList[0] = 0;
//        edgeList[1] = 1;
//        edgeList[2] = 2;
//    }
//    index = rand() % 2;
//    edge = edgeList[index];
//    
//    // Choose random exit cell from valid options.
//    int i = 0;
//    int j = 0;
//    int temp = 0;
//    index = 0;
//    int exitList[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//    int exitListSize = 0;
//    if (edge == 0) {
//        // Up
//        i = 0;
//        // j is random
//        index = 1;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[index][k] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        j = exitList[temp];
//    } else if (edge == 1) {
//        // Right
//        // i is random
//        j = size - 1;
//        index = size - 2;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[k][index] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        i = exitList[temp];
//    } else if (edge == 2) {
//        // Down
//        i = size - 1;
//        // j is random
//        index = size - 2;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[index][k] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        j = exitList[temp];
//    } else if (edge == 3) {
//        // Left
//        // i is random
//        j = 0;
//        index = size - 2;
//        for (int k = 1; k < size - 2; ++k) {
//            if (maze[k][index] == '.') {
//                exitList[exitListSize] = k;
//                exitListSize++;
//            }
//        }
//        temp = rand() % exitListSize;
//        i = exitList[temp];
//    }
//    
//    // Create exit
//    maze[i][j] = '.';
//}
