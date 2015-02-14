#include <iostream>

#include "Player.h"
#include "Game.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"


/**
 * Constructor
 */
Player::Player() {
    // Initialize stats
    _hp = 3;
    _attack = 0;
    _defense = 0;
}


/**
 * Initializes the player's position and sprite. Called by Unit's init() method.
 */
void Player::_init() {
    addSprite();
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


Vector2 Player::correctDirection(Vector2 position, Vector2 direction) {
    int newX = position.x + direction.x * 5;
    int newY = position.y + direction.y * 5;
    
    if ( _game->detectCollision(newX, position.y, 32, 32 ) ) direction.x = 0;
    if ( _game->detectCollision(position.x, newY, 32, 32 ) ) direction.y = 0;
    
    return direction;
}


/**
 * Adds the player sprite to the map.
 */
void Player::addSprite() {
    _sprite = new Sprite;
    _sprite->setResAnim(res::ui.getResAnim("player_front"));
    _sprite->attachTo(_view);
//    _sprite->setAnchor(Vector2(0.0f, 0.5f));
}


void Player::setFacing( Vector2 dir ) {
    if ( dir.y > 0 ) _sprite->setResAnim(res::ui.getResAnim("player_front"));
    if ( dir.y < 0 ) _sprite->setResAnim(res::ui.getResAnim("player_back"));
    if ( dir.x < 0 ) _sprite->setResAnim(res::ui.getResAnim("player_left"));
    if ( dir.x > 0 ) _sprite->setResAnim(res::ui.getResAnim("player_right"));
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
        dir = correctDirection( pos, dir );
        setFacing(dir);
		pos += dir * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
        setPosition(pos);
    }
}
