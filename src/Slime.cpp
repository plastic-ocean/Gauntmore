#include "res.h"
#include "Slime.h"
#include <cmath>


/**
 * Constructor. Initializes the stats
 */
Slime::Slime() {
    // Initialize the stats.
    _hp = 5;
    _attack = 4;
    _defense = 0;
    _speed = 50;
    _attackSpeed = 2;
    _lastTimeAttack = time(0);
}


/**
 * Returns the bounds of the Creature
 *
 * @return SDL_Rect that is the bounds for Creature
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
 * Puts a Creature sprite in the game
 */
void Slime::addSprite() {
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("slime_down"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    move();
}




/**
 * Plays the move animation.
 */
void Slime::move() {
    //_checkTween();
    switch (_facing) {
        case up:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_up")), 500, -1);
            break;
        case right:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_right")), 500, -1);
            break;
        case down:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_down")), 500, -1);
            break;
        case left:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_left")), 500, -1);
            break;
        default:
            break;
    }
}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Slime::_init() {
    addSprite();
    _setContents();
    findPath.setGame(_game);
}



/**
 * Updates the creature every frame. Called by Unit::update.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Slime::_update(const UpdateState &us) {
    Vector2 direction = moveMe();
    Vector2 position = getPosition();
    
    Facing prevFacing = _facing;
    _facing = getFacing(direction);
    if(_facing != prevFacing){
        move();
    }
    
    position += direction * (us.dt / 1000.0f) * _speed;
    setPosition(position);
    if((abs(position.x - _game->getPlayer()->getPosition().x) <= 70) && (abs(position.y - _game->getPlayer()->getPosition().y) <= 70)){
        time_t _current = time(0);
        if(_current >= _lastTimeAttack + _attackSpeed){
            _lastTimeAttack = time(0);
            damage();
            //cout << "attacking" << endl;
        }
    }
    
}