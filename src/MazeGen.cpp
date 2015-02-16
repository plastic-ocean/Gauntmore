#include <iostream>
#include <random>
#include "MazeGen.h"

using namespace std;

enum RoomType {deadend, straight, turn, branch, split, intersection, maze};

MazeGen::MazeGen(int size):_size(size), _wallListSize(0), _floorListSize(0) {
    // Seed rand.
    random_device randomDevice;
    srand(randomDevice.operator()());

    // Initialize the map.
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _maze[i][j] = '@';
        }
    }

    // Initialize the lists.
    for (int i = 0; i < _maxListSize; ++i) {
        _wallList[i][0] = 0;
        _wallList[i][1] = 0;

        _floorList[i][0] = 0;
        _floorList[i][1] = 0;
    }


//    _printMap();
}

/**
* Generates and returns a 2D matrix of Rooms.
*/
vector<vector<spRoom>> MazeGen::generate() {
    vector<vector<spRoom>> roomMap;
    size_t size = static_cast<size_t>(_size);
    roomMap.resize(size, vector<spRoom>(size, new Room));

    bool up;
    bool right;
    bool down;
    bool left;

    _createMaze();
    _printMap();

    // For each cell in _maze.
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            vector<bool> exitBools;
            up = false;
            right = false;
            down = false;
            left = false;

            if (_maze[i][j] != '@') {
                // See if there are surrounding rooms.
                if (i - 1 > 0 && _maze[i - 1][j] != '@') {
                    // Look up
                    up = true;
                }
                if (j + 1 < _size && _maze[i][j + 1] != '@') {
                    // Look right
                    right = true;
                }
                if (i + 1 < _size && _maze[i + 1][j] != '@') {
                    // Look down
                    down = true;
                }
                if (j - 1 > 0 && _maze[i][j - 1] != '@') {
                    // Look left
                    left = true;
                }

                exitBools.push_back(up);
                exitBools.push_back(right);
                exitBools.push_back(down);
                exitBools.push_back(left);

                // Use this information to choose a room type to put in the spRoom matrix.
                spRoom room;
                RoomType type = deadend;

                if ((up && !right && !down && !left) || (!up && right && !down && !left) ||
                        (!up && !right && down && !left) || (!up && !right && !down && left)) {
                    // dead end
                    type = deadend;
                    room = new Room(deadend, _size, exitBools);
                } else if ((up && !right && down && !left) || (!up && right && !down && left)) {
                    // straight
                    type = straight;
                    room = new Room(straight, _size, exitBools);
                } else if ((up && right && !down && !left) || (up && !right && !down && left) ||
                        (!up && right && down && !left) || (!up && !right && down && left)) {
                    // turn
                    type = turn;
                    room = new Room(turn, _size, exitBools);

                } else if ((!up && right && down && left) || (up && !right && down && left) ||
                        (up && right && !down && left) || (up && right && down && !left)) {
                    // branch/split
                    type = branch;
                    room = new Room(branch, _size, exitBools);

                } else if (up && right && down && left) {
                    // intersection
                    type = intersection;
                    room = new Room(intersection, _size, exitBools);
                }
//                cout << "maze room: " << i << ", " << j << " : " << type << " entrance: " << room->getEntrance().x << ", " << room->getEntrance().y << endl;

                roomMap[i][j] = room;
            }
        }
    }

    return roomMap;
}

/**
* Creates a 2D map array using Prim's algorithm for minimum spanning trees.
*/
void MazeGen::_createMaze() {
    int edge = _chooseEntrance();
    int index = 0;
    int wall[2];
    int count = 0;

    // While walls in wall list:
    while (_wallListSize > 1) {
        // Get a random wall from the list.
        index = rand() % (_wallListSize - 1);
        wall[0] = _wallList[index][0];
        wall[1] = _wallList[index][1];

        // Count adjacent cells already in the map.
        count = 0;
        for (int i = 0; i < _floorListSize; ++i) {
            if ((_floorList[i][0] == wall[0] - 1 && _floorList[i][1] == wall[1]) ||
                    (_floorList[i][0] == wall[0] && _floorList[i][1] == wall[1] + 1) ||
                    (_floorList[i][0] == wall[0] + 1 && _floorList[i][1] == wall[1]) ||
                    (_floorList[i][0] == wall[0] && _floorList[i][1] == wall[1] - 1)) {
                count++;
            }
        }

        int i = 0;
        int j = 0;
        // If only one of the adjacent cells is already in the map, continue.
        if (count == 1) {
            // Get the cell on the opposite side of the wall.
            i = 0; // cell column
            j = 0; // cell row
            if (_maze[wall[0] - 1][wall[1]] == '.') {
                // Check up
                // ###
                // #r#
                // #.#
                i = wall[0] + 1;
                j = wall[1];
            } else if (_maze[wall[0]][wall[1] + 1] == '.') {
                // Check right
                // ###
                // .r#
                // ###
                i = wall[0];
                j = wall[1] - 1;
            } else if (_maze[wall[0] + 1][wall[1]] == '.') {
                // Check down
                // #.#
                // #r#
                // ###
                i = wall[0] - 1;
                j = wall[1];
            } else if (_maze[wall[0]][wall[1] - 1] == '.') {
                // Check left
                // ###
                // #r.
                // ###
                i = wall[0];
                j = wall[1] + 1;
            }

            // Check if the cell on the opposite side of the chosen cell isn't in the map.
            if (_maze[i][j] == '@') {
                // Make the chosen cell part of the map.
                _maze[wall[0]][wall[1]] = '.';

                // Add it to the map list.
                _floorList[_floorListSize][0] = wall[0];
                _floorList[_floorListSize][1] = wall[1];
                _floorListSize++;

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
}


/**
* Adds all walls adjacent to map[i][j] to the wall list.
*
* @i is the i in map[i][j].
* @j is the j in map[i][j].
*/
void MazeGen::_addWall(int i, int j) {
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
* Chooses a random entrance, adds the first floor cell, and adds its walls to the wall list.
*
* @return the chosen edge.
*/
int MazeGen::_chooseEntrance() {
    int edge = rand() % 3;
    int i = 0; // entrance column
    int j = 0; // entrance row
    if (edge == 0) {
        // Top
        // #x#
        // #.#
        // ###
        i = 0;
        j = rand() % (_size - 2) + 1;
        _maze[i + 1][j] = '.';
        _maze[i][j] = 'x';
        i++;

        // Add adjacent walls.
        _addWall(i + 1, j);
        _addWall(i, j + 1);
        _addWall(i, j - 1);
    } else if (edge == 1) {
        // Right
        // ###
        // #.x
        // ###
        i = rand() % (_size - 2) + 1;
        j = _size - 1;
        _maze[i][j - 1] = '.';
        _maze[i][j] = 'x';
        j--;

        // Add adjacent walls.
        _addWall(i - 1, j);
        _addWall(i + 1, j);
        _addWall(i, j - 1);
    } else if (edge == 2) {
        // Bottom
        // ###
        // #.#
        // #x#
        i = _size - 1;
        j = rand() % (_size - 2) + 1;
        _maze[i - 1][j] = '.';
        _maze[i][j] = 'x';
        i--;

        // Add adjacent walls.
        _addWall(i - 1, j);
        _addWall(i, j + 1);
        _addWall(i, j - 1);
    } else if (edge == 3) {
        // Left
        // ###
        // x.#
        // ###
        i = rand() % (_size - 2) + 1;
        j = 0;
        _maze[i][j + 1] = '.';
        _maze[i][j] = 'x';
        j++;

        // Add adjacent walls.
        _addWall(i - 1, j);
        _addWall(i + 1, j);
        _addWall(i, j + 1);
    }

    // Add the floor cell to the map list.
    _floorList[_floorListSize][0] = i;
    _floorList[_floorListSize][1] = j;
    _floorListSize++;

    // Set entrance.
    setEntrance(Vector2(i, j));
    cout << "chooseExit: " << i << ", " << j << endl;

    return edge;
}


/**
* Choose a random map edge and cell for the exit.
*
* @edge is the entrance edge.
*/
int MazeGen::_chooseExit(int edge) {
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
* Prints the MazeGen map.
*/
void MazeGen::_printMap() {
    cout << endl;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            cout << _maze[i][j];
        }
        cout << endl;
    }
}
