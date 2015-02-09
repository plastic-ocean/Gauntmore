#include "Unit.h"
#include "Game.h"

/**
 * Constructor.
 */
Unit::Unit():_game(0), _dead(false) {}

/**
 * Initializes a unit.
 *
 * @pos is the units positon
 * @game is the game.
 */
void Unit::init(const Vector2 &pos, Game *game) {
	// Initialize game
	_game = game;
	_view = new Actor;
    _view->attachTo(game);
    _view->setPosition(pos);
    
    // Adds to global units list
    _game->pushUnit(this);

	//virtual method was overload in Player
	_init();
}

/**
 * Gets the units potions.
 *
 * @return the unit's position
 */
const Vector2& Unit::getPosition() {
    return _view->getPosition();
}

/**
 * Virtual method is overload in children.
 */
void Unit::update(const UpdateState &us) {
	_update(us);
}