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
 * Returns the direction the creature should face based off a direction.
 *
 * @direction a pair of ints (-1, 0, 1) that we use to detemine direction.
 * @return a Facing enum
 */
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


/**
 * Damages the player.
 */
void Creature::damage() {
    _game->getPlayer()->updateHealth(-_attack);
}


/**
 * Figures out which direction the creature should move.
 *
 * @returns a vector2 of ints (-1, 0, 1) which is used to set facing.
 */
Vector2 Creature::moveMe() {
    return findPath.setDirection(getPosition() );
}


/**
 * Gives the creature gold or a potion.
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
 * Puts the creatures contents on the ground when it dies.
 */
void Creature::_dropContents() {
    if (_contents) {
        _contents->init(getPosition(), _game);
        _contents->setLocation(getPosition());
        _game->getMap()->getRoom()->getUnits()->push_back(_contents);
    }
}


/**
 * Reduces the creature's hit points.
 */
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