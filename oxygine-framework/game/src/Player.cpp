#include "Player.h"
#include "Game.h"
#include "res.h"
#include "Joystick.h"
#include "Tmx.h"

void Player::_init() {
	//initialize player
	_view->setPosition(_game->getSize()/2);

    _human = new Sprite;
    _human->setResAnim(res::ui.getResAnim("human"));
    _human->attachTo(_view);
    _human->setAnchor(Vector2(0.5f, 0.5f));
}

void Player::_update(const UpdateState &us) {
	Vector2 dir;
	if (_game->_move->getDirection(dir)) {
		//update player position according to delta time and finger direction from virtual joystick
		Vector2 pos = _view->getPosition();		
		pos = pos + dir * (us.dt / 1000.0f) * 5;
		_view->setPosition(pos);
	}
}

void Player::_detectCollision() {
//    Tmx::RectT spriteRect = new Tmx::RectT(_view.getPosition().x, _view.getPosition().y, 32, 32);
}
