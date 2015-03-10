#include <cmath>
#include <iostream>
#include "Creature.h"
#include "Potion.h"
#include "Gold.h"
#include "res.h"
#include <cmath>


/**
 * Constructor
 */
Creature::Creature() {
    setType("creature");
}


/**
 *
 *
 */
void Creature::_setContents() {
    int randNum = rand() % 2;
    
    if (randNum == 0) {
        int randContents = rand() % 2;
        if (randContents == 0) {
            _contents = new Potion();
        } else {
            _contents = new Gold();
        }
    }
}


/**
 *
 *
 */
void Creature::_dropContents() {
    if (_contents) {
        _contents->init(getPosition(), _game);
        _contents->setLocation(getPosition());
        _game->getMap()->getRoom()->getUnits()->push_back(_contents);
    }
}


void Creature::damage() {
    _game->getPlayer()->updateHealth(-_attack);
}


Creature::Facing Creature::getFacing(Vector2 direction){
    if((direction.x == 1 && direction.y == 0)){
        // if direction is moving east or northeast or southeast
        return right;
    }else if ((direction.x == 0 && direction.y == 1)
              || (direction.x == -1 && direction.y == 1)
              || (direction.x == 1 && direction.y == 1)){
        // if direction is moving north
        return up;
    }else if((direction.x == 0 && direction.y == -1)
             || (direction.x == -1 && direction.y == -1)
             || (direction.x == 1 && direction.y == -1)){
        // if moving south
        return down;
    } else{
        // if moving west or north west or south west
        return left;
    }
}


Vector2 Creature::moveMe() {
    return findPath.setDirection(getPosition() );
}


void Creature::_interact() {
    int damage = _game->getPlayer()->getAttack();
    _hp -= damage;
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
//void Creature::_update(const UpdateState &us) {
//    
//    Vector2 direction = moveMe();
//    Vector2 position = getPosition();
//    
//    Facing prevFacing = _facing;
//    _facing = getFacing(direction);
//    if (_facing != prevFacing){
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