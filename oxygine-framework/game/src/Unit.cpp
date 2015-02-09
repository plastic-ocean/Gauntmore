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
	// Initialize the game.
	_game = game;
    
    // Attach the Unit (as an Actor) to the game.
	_view = new Actor;
    _view->attachTo(game);
    _view->setPosition(pos);
    
    // Add to Game's units list.
    _game->pushUnit(this);

	// Virtual method that is overload by children.
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