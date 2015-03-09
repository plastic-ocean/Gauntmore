#include "res.h"
#include "Bat.h"
#include <cmath>


/**
 * Constructor
 */
Bat::Bat() {
    // Initialize the stats.
    _hp = 2;
    _attack = 2;
    _defense = 0;
    _speed = 150;
    _attackSpeed = 2;
    _lastTimeAttack = time(0);
}

/**
 *
 *
 */
SDL_Rect Bat::getBounds() {
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
bool Bat::isPotion() {
    return false;
}


void Bat::addSprite() {
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("bat_down"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    move();
}

/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Bat::_init() {
    addSprite();
    _setContents();
    findPath.setGame(_game);
}


/**
 * Plays the move animation.
 */
void Bat::move() {
    //_checkTween();
    switch (_facing) {
        case up:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("bat_up")), 500, -1);
            break;
        case right:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("bat_right")), 500, -1);
            break;
        case down:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("bat_down")), 500, -1);
            break;
        case left:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("bat_left")), 500, -1);
            break;
        default:
            break;
    }
}


//void Bat::_interact() {
//    int damage = static_cast<int>(ceil(_game->getPlayer()->getAttack() / _defense));
//    _hp -= damage;
//    if (_hp == 0) {
//        // The creature is dead, hide it with an alpha tween.
//        _dead = true;
//        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
//        _dropContents();
//    }
//}


/**
 * Updates the creature every frame. Called by Unit::update.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
//void Bat::_update(const UpdateState &us) {
//    
//    Vector2 direction = moveMe();
//    Vector2 position = getPosition();
//    
//    Facing prevFacing = _facing;
//    _facing = getFacing(direction);
//    if(_facing != prevFacing){
//        move();
//    }
//    
//    position += direction * (us.dt / 1000.0f) * _speed;
//    setPosition(position);
//    if((abs(position.x - _game->getPlayer()->getPosition().x) <= 70) && (abs(position.y - _game->getPlayer()->getPosition().y) <= 70)){
//        
//        time_t _current = time(0);
//        if(_current >= _lastTimeAttack + _attackSpeed){
//            _lastTimeAttack = time(0);
//            damage();
//            //cout << "attacking" << endl;
//        }
//    }
//}