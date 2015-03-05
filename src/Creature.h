#ifndef __gauntmore__Creature__
#define __gauntmore__Creature__

#include "Unit.h"
#include "PathFinder.h"
#include "Game.h"
#include "Player.h"
#include "Thing.h"
#include "CreatureMover.h"


DECLARE_SMART(Creature, spCreature);
class Creature : public Unit {
    
public:
    Creature();
    
    enum Facing {up, right, down, left};
    
//    Facing getFacing() {
//        return _facing;
//    }
//    
//    void setFacing(Facing facing) {
//        _facing = facing;
//    }
    
//    virtual void attack() = 0;
//    
//    virtual void move(Facing facing) = 0;

protected:
    spThing _contents;

    PathFinder findPath;
    CreatureMover moveQ;

    /**
     *
     *
     */
    bool _alerted = false;
    
    Vector2 moveMe();
    
    /**
     *
     *
     */
    void _setContents();
    
    /**
     *
     *
     */
    void _dropContents();
    
    /**
     * Initializes a creatures position and sprite. Called by Unit's init() method.
     */
    virtual void _init() = 0;
    
    /**
     * Reduces the creature's hit points.
     */
    virtual void _interact() = 0;
    
    /**
     * Updates the creature every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    virtual void _update(const UpdateState &us) = 0;
};

#endif /* defined(__gauntmore__Creature__) */