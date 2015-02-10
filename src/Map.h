#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Map, spMap);
class Map : public Object {
    
public:
    Map(int size);
    
    /**
     * Get map entrance.
     */
    Vector2 getEntrance();
    
    /**
     * Set map entrance.
     *
     * @x is the entrance's x coordinate on the map.
     * @y is the entrance's y coordinate on the map.
     */
    void setEntrance(int x, int y);
    
    /**
     * Creates a 2D maze array using Prim's algorithm for minimum spanning trees.
     */
    void createMaze();
    
    /**
     * Prints the maze.
     */
    void printMaze();
    
private:
    const static int _maxMazeSize = 30;
    const static int _maxListSize = _maxMazeSize * _maxMazeSize;
    
    int _size;
    char _maze[_maxMazeSize][_maxMazeSize];
    
    int _wallListSize;
    int _wallList[_maxListSize][2];
    
    int _mazeListSize;
    int _mazeList[_maxListSize][2];
    
    Vector2 _entrance;
    
    /**
     * Adds all walls adjacent to maze[i][j] to the wall list.
     *
     * @i is the i in maze[i][j].
     * @j is the j in maze[i][j].
     */
    void _addWall(int i, int j);
    
    /**
     * Creates a tile map (.tmx file) from the 2D maze array.
     */
    void _createTileMap();
};
