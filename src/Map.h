#pragma once
#include "oxygine-framework.h"

#include "Unit.h"
#include "Room.h"
#include "Game.h"

using namespace oxygine;
using namespace std;

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
    
    /*
     Gets map size
     */
    int getSize();
    
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
    * Change to another room in on the map.
    */
    void changeRoom(int edge);

    spRoom getRoom() {
        return _room;
    }

    void setRoom(spRoom &_room) {
        Map::_room = _room;
    }

//    vector<spRoom> getRooms() {
//        return _rooms;
//    }
//
//    void setRooms(vector<spRoom> rooms) {
//        _rooms = rooms;
//    }
//
//    void addRoom(spRoom room) {
//        _rooms.push_back(room);
//    }

    vector<vector<spRoom>> getRoomMap() {
        return _roomMap;
    }

    void setRoomMap(vector<vector<spRoom>> roomMap) {
        _roomMap = roomMap;
    }

    int getCol() const {
        return _col;
    }

    void setCol(int col) {
        Map::_col = col;
    }

    int getRow() const {
        return _row;
    }

    void setRow(int row) {
        Map::_row = row;
    }

private:
    spRoom _room;
    vector<vector<spRoom>> _roomMap;
    Vector2 _entrance;

    // Current location in the map (the maze)
    int _col;
    int _row;

};
