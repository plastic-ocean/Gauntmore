#include <iostream>

#include "Player.h"
#include "Game.h"
#include "res.h"
#include "KeyboardInput.h"
#include "Tmx.h"
#include "SDL.h"

/**
 * Constructor
 */
Player::Player() {}

/**
 * Initializes the player's position and sprite. Called by Unit's init() method.
 */
void Player::_init() {
    // Initialize stats
    _hp = 3;
    _attack = 0;
    _defense = 0;
    
    // Sets the initial position in the game scene.
	_view->setPosition(_game->getSize() / 2);
    
    // Add sprite to the game scene.
    _sprite = new Sprite;
    _sprite->setResAnim(res::ui.getResAnim("hero"));
    _sprite->attachTo(_view);
//    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}


/**
 * Reduces the player's hit points.
 */
void Player::damage() {
    _hp--;
    if (_hp == 0) {
        // The create is dead, hide it with an alpha tween.
        _dead = true;
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        
        // TODO end the game
    }
}

void setDirection(Vector2 _dir) {

    
}
/**
 * Updates the player every frame.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Player::_update(const UpdateState &us) {
	Vector2 dir;
	if (_game->getMove()->getDirection(dir)) {
        
		Vector2 pos = getPosition();
		pos = pos + dir * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
        if (!_game->detectCollision(pos.x, pos.y, 32, 32)) {
            setPosition(pos);
        }
	}
}
