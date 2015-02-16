#include <iostream>
#include "Map.h"
#include "Room.h"
#include "MazeGen.h"
#include "Room.h"

using namespace std;


enum RoomType {deadend, straight, turn, branch, split, intersection, maze};


/**
* Constructor.
*/
Map::Map(int size) {
    spMazeGen mazeGen = new MazeGen(size);
    _roomMap = static_cast<vector<vector<spRoom>>>(mazeGen->generate());
    _entrance = mazeGen->getEntrance();
    int col = static_cast<int>(_entrance.x);
    int row = static_cast<int>(_entrance.y);

    _room = _roomMap[col][row];

    _room->createTileMap();

//    _room->printMap();
//    cout << "map: " << col << ", " << row << " : " << _room->getType() << " entrance: " << _room->getEntrance().x << ", " << _room->getEntrance().y << endl;
}

void Map::changeRoom(int edge) {
    // if exit has not been used
//    int size = getRoom()->getSize();
//    _room = new Room(split, size);
//    _rooms.push_back(_room);
    // else
    // find room and switch
}

/*
 need a way to find out what exit I'm leaving through,
 - idea 1
 create a vector2 for each exit location, store in a map
 when the player leaves the map, access
 map<Vector2 exitLocation, Room> roomMap;
 rooms keep a map like this so they know about their surrounding rooms

 - idea 2
 keep a vector<vector<Room>> _roomMap
 this is the map of rooms
 when the player leaves the current Room,
 find out the exit edge,
 use that to access the next room in the 2D vector
 the roomMap is a maze!
 */