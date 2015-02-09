#pragma once
#include "Unit.h"


DECLARE_SMART(Player, spPlayer);


class Player: public Unit {
    
public:
	
protected:
    spSprite _sprite;
    
    /**
     * Initializes the player.
     */
	void _init();
    
    /**
     * Updates the player every frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void _update(const UpdateState &us);
};
