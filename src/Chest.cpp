//
//  Chest.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/13/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "Chest.h"
#include "Gold.h"
#include "Potion.h"
#include "Game.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"


/**
 * Constructor
 */
Chest::Chest():_isOpen(false), _contents(0) {}


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
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    int randContents = rand() % 2;
    if (randContents == 0) {
        _contents = new Potion();
    }
    else{
        _contents = new Gold();
    }

}

/**
 * Interaction method for Chest.
 * Sets _open to true and removes chest from game.
 */
void Chest::_interact() {
    _isOpen = true;
    
    // The chest is open, hide it with an alpha tween.
    _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
    
    _contents->init(getPosition(), _game);
}



/**
 * Updates the Chest every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Chest::_update(const UpdateState &us) {
//    Vector2 isOpen;
    
}