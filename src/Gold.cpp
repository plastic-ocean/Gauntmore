#include "Gold.h"
#include "res.h"
#include "Game.h"


/**
 *  Constructor.
 */
Gold::Gold():_value(10) {
    setType("gold");
}


/**
 *  Gets bounds of the unit Gold.
 *  @return: SDL_Rect _bounds which is the bounds of Gold.
 */
SDL_Rect Gold::getBounds() {
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
void Gold::addSprite() {
    _sprite = new Sprite;
    _sprite->addTween(TweenAnim(resources.getResAnim("gold")), 500, -1);;
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


/**
 * Initializes a Gold position and sprite. Called by Unit's init() method.
 */
void Gold::_init() {
    addSprite();
}


/**
 *  Adds gold value to the player's current total.
 *  Removes sprite from the game.
 */
void Gold::_interact() {
    if (!isDead()) {
        _game->updateGoldCount(_value);
        
        // remove sprite
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dead = true;
    }
}


/**
 * Updates Gold every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Gold::_update(const UpdateState &us) {
}