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
    
    void createRoom();
    
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
     * Randomly chooses an entrance, adds the first floor cell, and adds its walls to the wall list.
     *
     * @return the chosen edge.
     */
    int _chooseEntrance();
    
    /**
     * Choose a random maze edge and cell for the exit.
     *
     * @edge is the entrance edge.
     */
    int _chooseExit(int edge);
    
    /**
     * Return true if the maze exit has been reached, otherwise false.
     *
     * @row is the row to check.
     * @col is the col to check.
     */
    bool _atExit(int row, int col);
    
    /**
     * Creates a tile map (.tmx file) from the 2D maze array.
     */
    void _createTileMap();
    
    /**
     * Returns a number betweeen start and finish inclusive.
     *
     * @start is the beginning of the range.
     * @finish is the end of the range, inclusive.
     */
    int _getRand(int start, int finish);
    
    void _drawRoom(int row, int col, int height, int width);
    
    void _drawConnectHallCol(int col, int begin, int end);
    
    void _drawConnectHallRow(int row, int begin, int end);
};
