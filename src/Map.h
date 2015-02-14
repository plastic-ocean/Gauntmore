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
     * Creates and draws a room on the map. Checks if the main hall is on a row or a column.
     * Then checks if there is space above or below a row and left or right of a column.
     * Connects the room(s) to the main hall with connecting halls.
     */
    void createHallMap(int exists);
    
    /**
     * Prints the map.
     */
    void printMap();
    
private:
    const static int _maxSize = 30;
    const static int _maxListSize = _maxSize * _maxSize;
    
    int _size;
    char _map[_maxSize][_maxSize];
    
    int _wallListSize;
    int _wallList[_maxListSize][2];
    
    int _floorListSize;
    int _floorList[_maxListSize][2];
    
    Vector2 _entrance;
    
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
     * Return true if the map exit has been reached, otherwise false.
     *
     * @row is the row to check.
     * @col is the col to check.
     */
    bool _atExit(int row, int col);
    
    /**
     * Creates a tile map (.tmx file) from the 2D map array.
     */
    void _createTileMap();
    
    /**
     * Returns a number betweeen start and finish inclusive.
     *
     * @start is the beginning of the range.
     * @finish is the end of the range, inclusive.
     */
    int _getRand(int start, int finish);
    
    /**
     * Draws a room between row and height, col and width.
     *
     * @row is the room's row index.
     * @col is the room's column index.
     * @height is the room's height index.
     * @width is the room's width index.
     */
    void _drawRoom(int row, int col, int height, int width);
    
    /**
     * Draws a connecting hall on a column between a room and the main hall.
     *
     * @col is the hall's column index.
     * @begin is the row index to begin on.
     * @end is the row index to end on.
     */
    void _drawConnectHallCol(int col, int begin, int end);
    
    /**
     * Draws a connecting hall on a row between a room and the main hall.
     *
     * @row is the hall's row index.
     * @begin is the column index to begin on.
     * @end is the column index to end on.
     */
    void _drawConnectHallRow(int row, int begin, int end);
};
