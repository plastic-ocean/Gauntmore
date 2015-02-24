#include "Chest.h"
#include "Gold.h"
#include "Potion.h"
#include "Game.h"
#include "Map.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"


/**
 * Constructor
 */
Chest::Chest():_isOpen(false), _contents(0) {}


SDL_Rect Chest::getBounds(){
    Vector2 unitPosition = getPosition();
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    return _bounds;
}


/**
 * Initializes a Chest position and sprite. Called by Unit's init() method.
 */
void Chest::_init() {
    addSprite();
    _setContents();
}

void Chest::addSprite() {
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("chest"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}

/**
 * Interaction method for Chest.
 * Sets _open to true and removes chest from game.
 */
void Chest::_interact() {
    if (!_isOpen) {
        _isOpen = true;
        _dead = true;
        
        // The chest is open, hide it with an alpha tween.
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        
        _contents->init(getPosition(), _game);
        _game->getMap()->getRoom()->getUnits()->push_back(_contents);
    }
}


void Chest::_setContents() {
    int randContents = rand() % 2;
    if (randContents == 0) {
        _contents = new Potion();
    }
    else{
        _contents = new Gold();
    }
}

/**
 * Updates the Chest every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Chest::_update(const UpdateState &us) {
//    Vector2 isOpen;
    
}