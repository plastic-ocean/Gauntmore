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
    
    Facing getFacing(Vector2 direction);
    
    void damage();
    
    virtual void move() = 0;

protected:
    Facing _facing;
    time_t _lastTimeAttack;
    spThing _contents;

    PathFinder findPath;

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
     * Updates the creature every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
    
    /**
     * Reduces the creature's hit points.
     */
    void _interact();
    
    /**
     * Initializes a creatures position and sprite. Called by Unit's init() method.
     */
    virtual void _init() = 0;
};

#endif /* defined(__gauntmore__Creature__) */