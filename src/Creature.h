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

    /**
     * Gets the Creature's facing.
     */
    Facing getFacing(Vector2 direction);

    /**
     * Attacks the player.
     */
    virtual void attack();

protected:
    time_t _lastTimeAttack;
    spThing _contents;

    PathFinder _findPath;
    CreatureMover _moveQ;

//    bool _alerted = false;

    /**
     * Moves the creature.
     */
    Vector2 _moveMe();
    
    /**
     * Sets the creature's item, if it has one.
     */
    void _setContents();
    
    /**
     * Drops the creature's item, if it has one.
     */
    void _dropContents();
    
    /**
     * Initializes a creatures position and sprite. Called by Unit's init() method.
     */
    virtual void _init() = 0;
    
    /**
     * Reduces the creature's hit points.
     */
    virtual void _interact();
    
    /**
     * Updates the creature every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    virtual void _update(const UpdateState &us) = 0;
};

#endif /* defined(__gauntmore__Creature__) */