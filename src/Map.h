#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Map, spMap);
class Map : public Object {
    
public:
    Map();
    
    /**
     * Adds all walls to list that are adjacent to maze[i][j].
     *
     * @size is the wall list size.
     * @walls is the current list of walls.
     * @i is the i in maze[i][j].
     * @j is the j in maze[i][j].
     */
    int addWall(int wallListSize, int maxWallListSize, int wallList[maxWallListSize][2], int mazeSize, char maze[mazeSize][mazeSize], int i, int j);
    
    /**
     * Creates a 2-D maze array using Prim's algorithm for minimum spanning trees.
     *
     * @size is the size of the maze.
     * @maze is the 2-D maze array.
     */
    void createMaze(int size, char maze[size][size]);
    
private:
    
};
