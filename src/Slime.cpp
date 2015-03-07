#include "res.h"
#include "Slime.h"


/**
 * Constructor
 */
Slime::Slime() {
    // Initialize the stats.
    _hp = 3;
    _attack = 1;
    _defense = 0;
    
}

/**
 *  Gets bounds of the unit Slime.
 *  @return: SDL_Rect _bounds which is the bounds of Slime.
 */
SDL_Rect Slime::getBounds() {
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
bool Slime::isPotion() {
    return false;
}

/**
 *  Method that does damage to the Player.
 */
void Slime::damage() {

}

/**
 *  Adds Sprite and attaches it to the game.
 */
void Slime::addSprite() {
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("slime_down"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}

/**
 * Initializes a Slime position and sprite. Called by Unit's init() method.
 */
void Slime::_init() {
    addSprite();
    _setContents();
}

/**
 * Interaction method for Slime.
 */
void Slime::_interact() {
    _hp--;
    if (_hp == 0) {
        // The creature is dead, hide it with an alpha tween.
        _dead = true;
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dropContents();
    }
}

/**
 * Updates the creature every frame. Called by Unit::update.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Slime::_update(const UpdateState &us) {
//    cout << "creature update" << endl;
    Vector2 direction = moveMe();
    Vector2 position = getPosition();
    position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
    setPosition(position);
}