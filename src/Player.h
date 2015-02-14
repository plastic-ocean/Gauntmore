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
    
    /**
     * Add sprite to the game scene.
     */
    void addSprite();
    
    void removeSprite();
    
protected:
    Vector2 correctDirection(Vector2 position, Vector2 direction);
    
    /**
     * Initializes the player's position and sprite. Called by Unit's init() method.
     */
	void _init();
    
    void setFacing(Vector2 dir);
    
    /**
     * Updates the player every frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void _update(const UpdateState &us);
};
