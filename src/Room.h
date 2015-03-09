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
    Room(int type, int size, vector<bool> exitBools);

    /**
    * Creates a room map.
    *
    * @type is the room type.
    */
    void createRoom();

    /**
    * Creates a tile map (.tmx file) from the 2D map array.
    */
    void createTileMap(string file);

    /**
    * Prints the map.
    */
    void printMap();


    /* Setters and Getters */
    
    /**
     * Gets the size of the room.
     */
    int getSize() const;

    /**
     * Sets the size of the room.
     */
    void setSize(int size);

    /**
     * Gets the entrance of the room.
     */
    Vector2 getEntrance();

    /**
     * Sets the entrance to the room.
     */
    void setEntrance(Vector2 entrance);

    /**
     * Gets the tiles list.
     */
    vector<SDL_Rect> getTiles();

    /**
     * Sets the tiles list.
     */
    void setTiles(vector<SDL_Rect> tiles);

    /**
     * Gets the units list.
     */
    list<spUnit>* getUnits();

    /**
     * Gets the room tyle
     */
    int getType();

    /**
     * Gets the exist vector.
     */
    vector<Vector2> getExits();

    /**
     * Sets the exists vector.
     */
    void setExits(vector<Vector2> exits);

    /**
     * Gets the top exit column.
     */
    int getTop();

    /**
     * Sets the top exit column.
     */
    void setTop(int top);

    /**
     * Gets the right exit row.
     */
    int getRight();

    /**
     * Sets the right exit row.
     */
    void setRight(int right);

    /**
     * Gets the bottom exit column.
     */
    int getBottom();

    /**
     * Sets the bottom exit column.
     */
    void setBottom(int bottom);

    /**
     * Gets the left exit row.
     */
    int getLeft();

    /**
     * Sets the left exit row.
     */
    void setLeft(int left);

private:
    const int tileSize = 64;

    vector<SDL_Rect> _tiles;

    list<spUnit> _units;

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
    * Copies one of the outside tile maps (.tmx) to room.tmx.
    */
    void _createOutsideTileMap(string tmxFile);

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
    * Creates an empty room.
    */
    void _createEmpty();
    
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