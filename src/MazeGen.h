#pragma once
#include "oxygine-framework.h"
#include "Room.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(MazeGen, spMazeGen);
class MazeGen : public Object {

public:
    MazeGen(int size);

    vector<vector<spRoom>> generate();

    int getSize() {
        return _size;
    }

    void setSize(int size) {
        _size = size;
    }

    Vector2 getEntrance() {
        return _entrance;
    }

    void setEntrance(Vector2 entrance) {
        _entrance = entrance;
    }

private:
    const static int _maxSize = 30;
    const static int _maxListSize = _maxSize * _maxSize;

    int _size;
    char _maze[_maxSize][_maxSize];
//    vector<vector<int>> _map;

    int _wallListSize;
    int _wallList[_maxListSize][2];

    int _floorListSize;
    int _floorList[_maxListSize][2];

    Vector2 _entrance;

    /**
    * Creates a 2D maze array using Prim's algorithm for minimum spanning trees.
    */
    void _createMaze();

    /**
    * Adds all walls adjacent to map[i][j] to the wall list.
    *
    * @i is the i in map[i][j].
    * @j is the j in map[i][j].
    */
    void _addWall(int i, int j);

    /**
    * Randomly chooses an entrance, adds the first floor cell, and adds its walls to the wall list.
    *
    * @return the chosen edge.
    */
    int _chooseEntrance();

    /**
    * Choose a random map edge and cell for the exit.
    *
    * @edge is the entrance edge.
    */
    int _chooseExit(int edge);

    /**
    * Prints the map.
    */
    void _printMap();
};