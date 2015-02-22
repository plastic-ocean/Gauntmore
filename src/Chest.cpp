//
//  Chest.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/13/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "Chest.h"
#include "Gold.h"
#include "Game.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"


/**
 * Constructor
 */
Chest::Chest(){
    _open = false;
    
}

/**
 * Interaction method for Chest.
 * Sets _open to true and removes chest from game.
 */
void Chest::interact(){
    _open = true;
    
    // The chest is open, hide it with an alpha tween.
    _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
}


void _chooseContents() {
    // choose a random # (0-1)
    // if potion:
    //    _contests = potion;
    // else:
    //    _contents = gold;
}


/**
 * Initializes a Chest position and sprite. Called by Unit's init() method.
 */
void Chest::_init() {
    // Initialize the stats.
    
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("chest"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    
    Vector2 unitPosition = getPosition();
    // these are adjusted for a skeleton sprite, we will need to make different ones for
    // different sprites
    _bounds.x = unitPosition.x + 15;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 15;
    _bounds.w = 15;
}


/**
 * Updates the Chest every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Chest::_update(const UpdateState &us){
    Vector2 isOpen;
    
//    if (_game->getMove()->getDirection(dir)) {
//        Vector2 pos = getPosition();
//        dir = correctDirection( pos, dir );
//        setFacing(dir);
//        pos += dir * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
//        setPosition(pos);
//    }
    
}