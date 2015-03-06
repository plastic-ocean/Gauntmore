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
    findPath.setGame(_game);

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

/**
 * Plays the attack animation.
 */
void Skeleton::attack() {
//    switch (_facing) {
//        case up:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_up")), 500);
//            break;
//        case right:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_right")), 500);
//            break;
//        case down:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_down")), 500);
//            break;
//        case left:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_left")), 500);
//            break;
//        default:
//            break;
//    }
}



/**
 * Plays the move animation.
 */
void Skeleton::move() {
    //_checkTween();
//    switch (_facing) {
//        case up:
//            _sprite = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_up")), 500, -1);
//            break;
//        case right:
//            _sprite = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_right")), 500, -1);
//            break;
//        case down:
//            _sprite = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_down")), 500, -1);
//            break;
//        case left:
//            _sprite = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_left")), 500, -1);
//            break;
//        default:
//            break;
//    }
}

void Skeleton::addSprite(){
    // Add sprite to the game scene view.
    _facing = down;
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
    
    if((direction.x == 1 && direction.y == 0)
       || (direction.x == 1 && direction.y == 1)
       || (direction.x == 1 && direction.y == -1)){
        // if direction is moving east or northeast or southeast
        _facing = right;
        //move();
    }else if (direction.x == 0 && direction.y == 1){
        // if direction is moving north
        _facing = up;
        //move();
    } else if((direction.x == -1 && direction.y == 0)
              || (direction.x == -1 && direction.y == 1)
              || (direction.x == -1 && direction.y == -1)){
        // if moving west or north west or south west
        _facing = left;
        //move();
    }else if(direction.x == 0 && direction.y == -1){
        // if moving south
        _facing = down;
        //move();
    }
    
    position += direction * (us.dt / 1000.0f) * _speed; // CHANGE ME!!!!!!!!!!!
    setPosition(position);
    
    // if the abs of the two positions is less than equal to stopping distance then attack
    if((abs(position.x - _game->getPlayer()->getPosition().x) <= 70) && (abs(position.y - _game->getPlayer()->getPosition().y) <= 70)){
//        cout << "attacking" << endl;
        //sleep(1000);
    }
    
}