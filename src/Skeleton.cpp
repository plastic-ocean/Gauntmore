//
//  Skeleton.cpp
//  gauntmore_macosx
//
//  Created by benjamin barnes on 2/14/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "Skeleton.h"

#include "Creature.h"
#include "res.h"


/**
 * Constructor
 */
Skeleton::Skeleton(){}


/**
 * Reduces the creatures hit points.
 */



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
    _sprite->setResAnim(resources.getResAnim("skeleton"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


/**
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Skeleton::_update(const UpdateState &us) {
    // move the creature toward the player
}