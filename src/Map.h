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
     * Sets the current room a new room in the maze depending the given wall edge.
     *
     * @edge is the wall edge of the last room the player existed.
     */
    void changeRoom(int edge);
    
    /**
     * Gets the current room.
     */
    spRoom getRoom();
    
    /**
     * Sets the current room.
     */
    void setRoom(spRoom &room);

    /**
     * Gets the room map.
     */
    vector<vector<spRoom>> getRoomMap();
    
    /**
     * Sets the room map.
     */
    void setRoomMap(vector<vector<spRoom>> roomMap);
    
    /**
     * Gets the current column in the maze.
     */
    int getCol() const;
    
    /**
     * Sets the current column in the maze.
     */
    void setCol(int col);
    
    /**
     * Gets the current row in the maze.
     */
    int getRow() const;
    
    /**
     * Sets the current row in the maze.
     */
    void setRow(int row);

private:
    spRoom _room;
    vector<vector<spRoom>> _roomMap;
    pair<int, int> _entrance;

    // Current location in the map (the maze)
    int _col;
    int _row;

    /**
    * Checks if the current room is an outside room.
    *
    * @return a file string.
    */
    string _getTmxFile();
};
