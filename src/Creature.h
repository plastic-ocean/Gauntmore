#pragma once
#include "Unit.h"
#include "PathFinder.h"
#include "Game.h"
#include "Player.h"
#include "CreatureMover.h"

DECLARE_SMART(PathFinder, spPathFinder);
DECLARE_SMART(CreatureMover, spCreatureMover);
DECLARE_SMART(Creature, spCreature);
class Creature: public Unit {
    
public:
    Creature();
    
    /**
     * Reduces the creatures hit points.
     */
    void damage();
    
private:
    spPathFinder findPath;
    spCreatureMover moveQ;
    
    /**
     * Initializes a creatures position and sprite. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Updates the creature every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};