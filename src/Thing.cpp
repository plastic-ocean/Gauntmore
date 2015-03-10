#include "SDL.h"
#include "tmx/Tmx.h"

#include "Thing.h"
#include "Game.h"
#include "res.h"


/**
 * Constructor
 */
Thing::Thing() {
    setType("thing");
}


/**
 * Interaction method for Thing.
 */
void Thing::interact(){
}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Thing::_init() {
}


/**
 * Updates the Thing every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Thing::_update(const UpdateState &us) {}
