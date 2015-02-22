#include "Potion.h"
#include "Game.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"


/**
 * Constructor.
 */
Potion::Potion(){
    
}

/**
 * Interaction method for Potion.
 */
void Potion::interact(){
    
}

/**
 * Initializes position and sprite of Potion. Called by Unit's init() method.
 */
void Potion::_init(){
    // Initialize the stats.
    
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("potion"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    
}

/**
 * Updates the Potion every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Potion::_update(const UpdateState &us){
    
}