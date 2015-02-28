#ifndef __gauntmore__Creature__
#define __gauntmore__Creature__

#include "Unit.h"
#include "PathFinder.h"
#include "Game.h"
#include "Player.h"
#include "Thing.h"

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
    
//    spPathFinder findPath;
//    CreatureMover moveQ;
    
    /**
     *
     *
     */
    Vector2 moveMe();
    
    /**
     * Initializes a creatures position and sprite. Called by Unit's init() method.
     */
    void _init();
    
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
     * Reduces the creature's hit points.
     */
    void _interact();
    
    /**
     * Updates the creature every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Creature__) */