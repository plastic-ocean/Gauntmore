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
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Creature::_update(const UpdateState &us) {
    // move the creature toward the player
}


