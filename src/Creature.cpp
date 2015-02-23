#include "Creature.h"
#include "res.h"


/**
 * Constructor
 */
Creature::Creature() {}


/**
 * Reduces the creatures hit points.
 */
void Creature::damage() {
    _hp--;
    if (_hp == 0) {
        // The creature is dead, hide it with an alpha tween.
        _dead = true;
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
    }
}


/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Creature::_init() {
    // Initialize the stats.
    _hp = 3;
    _attack = 0;
    _defense = 0;
    
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim(""));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


/**
 * Updates the creature every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Creature::_update(const UpdateState &us) {
    // move the creature toward the player
    findPath->aStar(this->getPosition(), _game->getPlayer()->getPosition() );
    
}


