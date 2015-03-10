#include "Unit.h"
#include "Game.h"
#include "Map.h"
#include "KeyboardInput.h"

/**
 * Constructor.
 */
Unit::Unit():_game(0), _dead(false), _isPotion(false) {}


/**
 * Initializes a unit.
 *
 * @pos is the units position
 * @game is the game.
 */
void Unit::init(const Vector2 &pos, Game *game) {
	// Initialize the game.
	_game = game;
    
    attachUnit();
    setPosition(pos);

	// Virtual method that is overload by children.
	_init();
}


/**
 * Attaches the unit to the view.
 */
void Unit::attachUnit() {
    // Attach the Unit (as an Actor) to the game.
    _view = new Actor;
    _view->attachTo(_game);
}


/**
 * Detaches the unit from the view.
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


const Vector2& Unit::getPosition() {
    return _view->getPosition();
}


void Unit::setPosition(const Vector2& position) {
    _view->setPosition(position);
}


string Unit::getType() {
    return _type;
}


void Unit::setType(string type) {
    _type = type;
}


const bool Unit::isDead() {
    return _dead;
}


int Unit::getHp() {
    return _hp;
}


int Unit::getAttack() {
    return _attack;
}


int Unit::getDefense() {
    return _defense;
}


void Unit::setLocation(Vector2 location) {
    _location = location;
}


Vector2 Unit::getLocation() {
    return _location;
}


SDL_Rect Unit::getRect() {
    return _rect;
}


void Unit::setRect(SDL_Rect rect) {
    _rect = rect;
}


bool Unit::isPotion() {
    return _isPotion;
}