#include "res.h"
#include "Skeleton.h"


/**
 * Constructor
 */
Skeleton::Skeleton(){}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Skeleton::_init() {
    
    // Initialize the stats.
    _hp = 3;
    _attack = 0;
    _defense = 0;
    
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("human"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


void Skeleton::_interact() {
    
}


/**
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Skeleton::_update(const UpdateState &us) {
    // move the creature toward the player
}