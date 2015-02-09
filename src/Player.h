#pragma once
#include "Unit.h"

DECLARE_SMART(Player, spPlayer);
class Player: public Unit {
    
public:
	Player();
    
    /**
     * Reduces the player's hit points.
     */
    void damage();
    
protected:
    spSprite _sprite;
    
    /**
     * Initializes the player's position and sprite. Called by Unit's init() method.
     */
	void _init();
    
    /**
     * Updates the player every frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void _update(const UpdateState &us);
};
