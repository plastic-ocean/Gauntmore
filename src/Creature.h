#pragma once
#include "Unit.h"

DECLARE_SMART(Creature, spCreature);
class Creature: public Unit {
    
public:
    Creature();
    

    
private:
    /**
     * Initializes a creatures position and sprite. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Reduces the creatures hit points.
     */
    void _interact();
    
    /**
     * Updates the creature every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};