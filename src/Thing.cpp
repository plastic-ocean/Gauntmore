//
//  Thing.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/12/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "Thing.h"
#include "Game.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"



/**
 * Constructor
 */
Thing::Thing(){
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
    // Initialize the stats.
    
}



/**
 * Updates the Thing every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Thing::_update(const UpdateState &us){
    
}