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
    
    /**
     * Detects collisions between the player and the walls.
     *
     * @x is the x coordinate to check.
     * @y is the y coordinate to check.
     * @h is the height coordinate to check.
     * @w is the width coordinate to check.
     * @return true is there is a collision and false if there is not
     */
    bool detectCollision(int x, int y, int h, int w);
};
