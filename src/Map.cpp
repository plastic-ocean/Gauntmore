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
 * Creates a 2D maze array using Prim's algorithm for minimum spanning trees.
 */
void Map::createMaze() {
    // Randomly choose an entrance, add the first floor cell, and add its walls to the wall list.
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
    
    // Choose random maze edge for the exit.
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
    index = rand() % 2;
    edge = edgeList[index];
    
    // Choose random exit cell from valid options.
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
    
    _createTileMap();
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
