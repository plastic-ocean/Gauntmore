#include "Chest.h"
#include "Thing.h"
#include "Gold.h"
#include "Potion.h"
#include "Armor.h"
#include "Weapon.h"
#include "Game.h"
#include "Map.h"
#include "KeyboardInput.h"
#include "res.h"
#include "tmx/Tmx.h"
#include "SDL.h"
#include <list>


/**
 * Constructor
 */
Chest::Chest():_isOpen(false), _contents(0) {
    setType("chest");
}


/**
 *  Gets bounds of a chest.
 *  @return: SDL_Rect _bounds which is the bounds of a chest.
 */
SDL_Rect Chest::getBounds(){
    Vector2 unitPosition = getPosition();
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    return _bounds;
}


/**
 * Adds sprite and attachs it to the game.
 */
void Chest::addSprite() {
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("chest"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


/**
 * Initializes a Chest position and sprite. Called by Unit's init() method.
 */
void Chest::_init() {
    addSprite();
    _setContents();
}


/**
 * Interaction method for Chest.
 * Sets _open to true and removes chest from game.
 */
void Chest::_interact() {
    if (!_isOpen) {
        _isOpen = true;
        _dead = true;
        
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        
        _contents->init(getPosition(), _game);
        //        _contents->setLocation(getPosition());
        _game->getMap()->getRoom()->getUnits()->push_back(_contents);
    }
}

/**
 *  Sets the contents of a chest to either a Potion or Gold.
 */
void Chest::_setContents() {
    list<spThing> *_things = _game->getContentsList();
    int randNum = rand() % static_cast<int>(_things->size());
    int j = 0;
    
    for (list<spThing>::iterator i = _things->begin(); i != _things->end(); ++i) {
        j++;
        
        if (j == randNum) {
            spThing _thing = *i;
            _contents = _thing;
          //  cout << "_contents: " << _contents->getType() << endl;
            i = _things->erase(i);
        }
    }
}

/**
 * Updates the Chest every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Chest::_update(const UpdateState &us) {}