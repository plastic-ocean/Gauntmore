#include "Unit.h"
#include "Game.h"
#include "Map.h"
#include "KeyboardInput.h"

/**
 * Constructor.
 */
Unit::Unit():_game(0), _dead(false), _isPotion(false) {}


/**
 * Initializes a unit. When initializing any child this is the called method.
 * It calls the overloaded _init method for all children.
 *
 * @pos is the unit's position
 * @game is the game.
 */
void Unit::init(const Vector2 &pos, Game *game) {
	_game = game;
    
    attachUnit();
    setPosition(pos);

	_init();
}


/**
 *  Attaches the Unit to the game as an Actor.
 */
void Unit::attachUnit() {
    _view = new Actor;
    _view->attachTo(_game);
}


/**
 *  Detaches the Unit to the game as an Actor.
 */
void Unit::detachUnit() {
    _sprite->detach();
    _view->detach();
    _view = 0;
}


/**
 * Allows the player to interacts with the unit. Calls the _interact method in all children.
 */
void Unit::interact() {
    _interact();
}


/**
 * Updates all Units. Calls method _update that is is defined in children.
 */
void Unit::update(const UpdateState &us) {
    if (!_game->isPaused()) {
        setLocation(getPosition());
        _update(us);
    }
}


/* Getters and Setters */

/**
 * Gets current position.
 */
const Vector2& Unit::getPosition() {
    return _view->getPosition();
}



/**
 * Sets current position.
 */
void Unit::setPosition(const Vector2& position) {
    _view->setPosition(position);
}


/**
 * Gets current type.
 */
string Unit::getType() {
    return _type;
}


/**
 * Sets current position.
 */
void Unit::setType(string type) {
    _type = type;
}


/**
 * Determines whether unit is dead.
 */
const bool Unit::isDead() {
    return _dead;
}


/**
 * Gets current HP.
 */
int Unit::getHp() {
    return _hp;
}


/**
 * Gets current attack.
 */
int Unit::getAttack() {
    return _attack;
}


/**
 * Gets current defense.
 */
int Unit::getDefense() {
    return _defense;
}


/**
 * Sets current location.
 */
void Unit::setLocation(Vector2 location) {
    _location = location;
}


/**
 * Gets current location.
 */
Vector2 Unit::getLocation() {
    return _location;
}


/**
 * Gets current SDL Rectangle.
 */
SDL_Rect Unit::getRect() {
    return _rect;
}


/**
 * Sets current SDL Rectangle.
 */
void Unit::setRect(SDL_Rect rect) {
    _rect = rect;
}

/**
 * Checks if the Unit is a potion.
 */
bool Unit::isPotion() {
    return _isPotion;
}