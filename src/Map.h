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
     * Change to another room in on the map.
     */
    void changeRoom(int edge);

    spRoom getRoom();

    void setRoom(spRoom &room);

    vector<vector<spRoom>> getRoomMap();

    void setRoomMap(vector<vector<spRoom>> roomMap);

    int getCol() const;

    void setCol(int col);

    int getRow() const;

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
