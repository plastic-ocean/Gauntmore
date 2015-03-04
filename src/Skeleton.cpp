#include "res.h"
#include "Skeleton.h"


/**
 * Constructor
 */
Skeleton::Skeleton():_contents(0) {}

/**
 *  Gets bounds of the unit Skeleton.
 *  @return: SDL_Rect _bounds which is the bounds of Skeleton.
 */
SDL_Rect Skeleton::getBounds(){
    Vector2 unitPosition = getPosition();
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    return _bounds;
}

/**
 *  Boolean method to determine if the unit is a Potion.
 */
bool Skeleton::isPotion() {
    return false;
}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Skeleton::_init() {
    // Initialize the stats.
    _hp = 3;
    _attack = 2;
    _defense = 0;
    
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("skeleton"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    
    _setContents();
}

/**
 *
 *
 */
void Skeleton::_interact() {
    _hp--;
    if (_hp == 0) {
        // The creature is dead, hide it with an alpha tween.
        _dead = true;
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dropContents();
    }
}


/**
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Skeleton::_update(const UpdateState &us) {
    // move the creature toward the player
}