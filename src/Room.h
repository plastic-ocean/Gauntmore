#pragma once
#include "oxygine-framework.h"
#include "tmx/Tmx.h"
#include "Unit.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Room, spRoom);
class Room : public Object {
    
public:
    Room(int type, int size);

    typedef list<spUnit> Units;

    /**
    * Creates a room map.
    *
    * @type is the room type.
    */
    void createRoom(int exits);

    /**
    * Prints the map.
    */
    void printMap();

    int getSize() const {
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

    Tmx::Map *getTileMap() {
        return _tileMap;
    }

    void setTileMap(Tmx::Map *tileMap) {
        _tileMap = tileMap;
    }

    vector<SDL_Rect> getTiles() {
        return _tiles;
    }

    void setTiles(vector<SDL_Rect> tiles) {
        _tiles = tiles;
    }

    Units getUnits() {
        return _units;
    }

    void setUnits(list<spUnit> units) {
        _units = units;
    }

private:
    Tmx::Map *_tileMap;
    vector<SDL_Rect> _tiles;

    typedef list<spUnit> units;
    Units _units;

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
    * Creates a 2D maze array using Prim's algorithm for minimum spanning trees.
    */
    void _createMaze();

    /**
    * Creates and draws a room on the map. Checks if the main hall is on a row or a column.
    * Then checks if there is space above or below a row and left or right of a column.
    * Connects the room(s) to the main hall with connecting halls.
    */
    void _createHallMap(int exits);

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
    void _drawHallCol(int col, int begin, int end);

    /**
    * Draws a connecting hall on a row between a room and the main hall.
    *
    * @row is the hall's row index.
    * @begin is the column index to begin on.
    * @end is the column index to end on.
    */
    void _drawHallRow(int row, int begin, int end);
};