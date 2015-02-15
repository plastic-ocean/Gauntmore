#pragma once
#include "oxygine-framework.h"
#include "Unit.h"
#include "Room.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Map, spMap);
class Map : public Object {

public:
    Map(int size);

    void changeRoom(int edge);

    spRoom getRoom() const {
        return _room;
    }

    void setRoom(spRoom room) {
        _room = room;
    }

    vector<spRoom> getRooms() {
        return _rooms;
    }

    void setRooms(vector<spRoom> rooms) {
        _rooms = rooms;
    }

    void addRoom(spRoom room) {
        _rooms.push_back(room);
    }

private:
    spRoom _room;
    vector<spRoom> _rooms;
};