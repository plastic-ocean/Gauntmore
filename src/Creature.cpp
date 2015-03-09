#include <cmath>
#include <iostream>
#include "Creature.h"
#include "Potion.h"
#include "Gold.h"
#include "res.h"


/**
 * Constructor
 */
Creature::Creature() {
    setType("creature");
//    PathFinder findPath = PathFinder(_game);
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


/**
 * Reduces the creatures hit points.
 */
//void Creature::_interact() {
//    _hp--;
//    if (_hp == 0) {
//        // The creature is dead, hide it with an alpha tween.
//        _dead = true;
//        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
//        _dropContents();
//    }
//}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
//void Creature::_init() {
//    findPath.setGame(_game);//for collision detection
//    
//}



Vector2 Creature::moveMe() {
     
    return findPath.setDirection(getPosition() );}


/**
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
//void Creature::_update(const UpdateState &us) {
////    Vector2 direction = moveMe();
////    Vector2 position = getPosition();
////    position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
////    setPosition(position);
//
//}


