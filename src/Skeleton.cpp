#include "res.h"
#include "Skeleton.h"
#include <cmath>


/**
 * Constructor
 */
Skeleton::Skeleton():_contents(0) {
    _hp = 3;
    _attack = 2;
    _defense = 0;
    _speed = 200;
}

/**
 *
 *
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
 *
 *
 */
bool Skeleton::isPotion() {
    return false;
}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Skeleton::_init() {
    addSprite();
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

void Skeleton::damage(){
    
}

void Skeleton::addSprite(){
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
    // cout << "creature update" << endl;
    Vector2 direction = moveMe();
    Vector2 position = getPosition();
    position += direction * (us.dt / 1000.0f) * _speed; // CHANGE ME!!!!!!!!!!!
    setPosition(position);
    // if the abs of the two positions is less than equal to stopping distance then attack
    if((abs(position.x - _game->getPlayer()->getPosition().x) <= 70) && (abs(position.y - _game->getPlayer()->getPosition().y) <= 70)){
        cout << "attacking" << endl;
        //sleep(1000);
    }
    // this will damage player
    // facing and attack
}