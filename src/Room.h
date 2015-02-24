#pragma once
#include "oxygine-framework.h"
#include "tmx/Tmx.h"
#include "Unit.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Room, spRoom);
class Room : public Object {
    
public:
    Room();
    Room(Game *game, int type, int size, vector<bool> exitBools);

    typedef list<spUnit> Units;

    /**
    * Creates a room map.
    *
    * @type is the room type.
    */
    void createRoom();

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

    Units* getUnits() {
        return &_units;
    }

    void setUnits(Units units) {
        _units = units;
    }

    /**
    * Adds unit to the back of the units list.
    *
    * @unit is the Unit to be added.
    */
    void pushUnit(spUnit unit) {
        _units.push_back(unit);
    }
    
    void removeUnit(Units::iterator i) {
        _units.erase(i);
    }

    int getType() {
        return _type;
    }

    /**
    * Prints the map.
    */
    void printMap();

    /**
    * Creates a tile map (.tmx file) from the 2D map array.
    */
    void createTileMap();


    vector<Vector2> getExits() {
        return _exits;
    }

    void setExits(vector<Vector2> exits) {
        _exits = exits;
    }

    int getTop() {
        return _top;
    }

    void setTop(int _top) {
        Room::_top = _top;
    }

    int getRight() {
        return _right;
    }

    void setRight(int right) {
        _right = right;
    }

    int getBottom() {
        return _bottom;
    }

    void setBottom(int bottom) {
        _bottom = bottom;
    }

    int getLeft() {
        return _left;
    }

    void setLeft(int left) {
        _left = left;
    }


private:
    const int tileSize = 64;
    
    Game *_game;
    
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

    vector<bool> _exitBools;
    vector<Vector2> _exits;

    int _type;

// exit cells
    int _top;
    int _right;
    int _bottom;
    int _left;

    /**
    * Creates a straight hall.
    */
    void _createStraight();

    /**
    * Creates a hall ending in a room with no other exits.
    */
    void _createDeadEnd();

    /**
    * Creates a hall with a single turn.
    */
    void _createTurn();

    /**
    * Creates a straight hall with a single branch.
    */
    void _createBranch();

    /**
    * Creates two intersecting straight halls.
    */
    void _createIntersection();
    
    /**
    * Returns a number betweeen start and finish inclusive.
    *
    * @start is the beginning of the range.
    * @finish is the end of the range, inclusive.
    */
    int _getRand(int start, int finish);
    
    void _drawOpenSpaces(int row, int column, bool isColumn);

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




///**
//* Creates a 2D maze array using Prim's algorithm for minimum spanning trees.
//*/
//void _createMaze();
//
///**
//* Creates and draws a room on the map. Checks if the main hall is on a row or a column.
//* Then checks if there is space above or below a row and left or right of a column.
//* Connects the room(s) to the main hall with connecting halls.
//*/
//void _createHallMap(int exits);
///**
// * Adds all walls adjacent to map[i][j] to the wall list.
// *
// * @i is the i in map[i][j].
// * @j is the j in map[i][j].
// */
//void _addWall(int i, int j);
//
///**
// * Randomly chooses an entrance, adds the first floor cell, and adds its walls to the wall list.
// *
// * @return the chosen edge.
// */
//int _chooseEntrance();
//
///**
// * Choose a random map edge and cell for the exit.
// *
// * @edge is the entrance edge.
// */
//int _chooseExit(int edge);