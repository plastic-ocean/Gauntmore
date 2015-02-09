#include <iostream>

#include "Player.h"
#include "Game.h"
#include "res.h"
#include "KeyboardInput.h"
#include "Tmx.h"
#include "SDL.h"


/**
 * Initializes the player's position and sprite.
 */
void Player::_init() {
	_view->setPosition(_game->getSize() / 2);

    _sprite = new Sprite;
    _sprite->setResAnim(res::ui.getResAnim("human"));
    _sprite->attachTo(_view);
//    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


/**
 * Updates the player every frame.
 *
 * @us is the UpdateStatus sent by the global update method.
 */
void Player::_update(const UpdateState &us) {
	Vector2 dir;
	if (_game->_move->getDirection(dir)) {
		Vector2 pos = _view->getPosition();
		pos = pos + dir * (us.dt / 1000.0f) * 5;
        if (!_game->detectCollision(pos.x, pos.y, 32, 32)) {
            _view->setPosition(pos);
        }
	}
}
