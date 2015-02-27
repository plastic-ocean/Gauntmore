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
    }
}


/**
 * Reduces the creatures hit points.
 */
void Creature::_interact() {
    _hp--;
    if (_hp == 0) {
        // The creature is dead, hide it with an alpha tween.
        _dead = true;
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dropContents();
    }
}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Creature::_init() {
//    // Initialize the stats.
//    _hp = 3;
//    _attack = 0;
//    _defense = 0;
//    
//    // Add sprite to the game scene view.
//    _sprite = new Sprite;
//    _sprite->setResAnim(resources.getResAnim(""));
//    _sprite->attachTo(_view);
//    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}

/**
 *
 *
 */
Vector2 Creature::moveMe() {
    const int DEADZONE = 0;
    Vector2 moveDir = {0,0};
    Vector2 pPos = _game->getPlayer()->getPosition();//player's position
    Vector2 cPos = getPosition();//creature's position
    
    if ( abs(pPos.x - cPos.x) <= 64 && abs(pPos.y - cPos.y) <= 64 ) {
        return moveDir;//you are less than 64 pixels away, do nothing
    }
    //otherwise, check the movement Queue
    if ( moveQ.isEmpty() ) {
        std::cout << "moveQ is empty, attempting to fill it" << std::endl;
        moveQ.updatePath(findPath->aStar(pPos, cPos) );
    }
        
    //if the Q is NOT empty
        Vector2 nextSpot = moveQ.peekNext();//look at where you are going
        if ( abs(pPos.x - nextSpot.x) <= 10 && abs(pPos.y - nextSpot.y) <= 10) {
            moveQ.updatePath(findPath->aStar(pPos, cPos) );

            nextSpot = moveQ.peekNext();//start moving to the next spot
        }
    
    if ( (cPos.x - nextSpot.x) < -DEADZONE ) moveDir.x = 1;
    if ( (cPos.x - nextSpot.x) > DEADZONE ) moveDir.x = -1;
    if ( (cPos.y - nextSpot.y) < -DEADZONE ) moveDir.y = 1;
    if ( (cPos.y - nextSpot.y) > DEADZONE ) moveDir.y = -1;
    
    return moveDir;
}


/**
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Creature::_update(const UpdateState &us) {
    Vector2 direction = moveMe();
    Vector2 position = getPosition();
    position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
    setPosition(position);
    
}


