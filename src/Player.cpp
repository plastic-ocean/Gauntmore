#include <iostream>

#include "Player.h"
#include "Game.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Map.h"

/**
 * Constructor
 */
Player::Player(int hp, int attack, int defense) {
    // Initialize stats
    _hp = hp;
    _attack = attack;
    _defense = defense;
    _hasTween = false;
    facing = down;
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
    int newX = static_cast<int>(position.x) + static_cast<int>(direction.x) * 5;
    int newY = static_cast<int>(position.y) + static_cast<int>(direction.y) * 5;
    
    if ( _game->detectCollision(newX, static_cast<int>(position.y), 32, 32 ) ) direction.x = 0;
    if ( _game->detectCollision(static_cast<int>(position.x), newY, 32, 32 ) ) direction.y = 0;
    
    return direction;
}


/**
 * Adds the player sprite to the map.
 */
void Player::addSprite() {
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("player_front"));
    _sprite->attachTo(_view);
//    _sprite->setAnchor(Vector2(0.0f, 0.5f));
}


void Player::_setFacing(Vector2 dir) {
    if ( dir.y > 0 ) {
        _sprite->setResAnim(resources.getResAnim("player_front"));
        facing = down;
    }
    if ( dir.y < 0 ) {
        _sprite->setResAnim(resources.getResAnim("player_back"));
        facing = up;
    }
    if ( dir.x < 0 ) {
        _sprite->setResAnim(resources.getResAnim("player_left"));
        facing = left;
    }
    if ( dir.x > 0 ) {
        _sprite->setResAnim(resources.getResAnim("player_right"));
        facing = right;
    }
}

void Player::moveUp() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("player_move_back")), 300, -1);
}

void Player::moveDown() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("player_move_front")), 300, -1);
}

void Player::moveRight() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("player_move_right")), 300, -1);
}

void Player::moveLeft() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("player_move_left")), 300, -1);
}

void Player::_checkTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
    }
    _hasTween = true;
}

void Player::removeTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
    }
    _hasTween = false;
}

bool Player::_isExit(Vector2 position) {
    bool exit = false;
    int size = _game->getMap()->getRoom()->getSize() * 32;

    if (!(position.x > 0 && position.x < size - 32 && position.y > 0 && position.y < size - 32)) {
        exit = true;
        int edge = 0;

        if (position.y <= 0) {
            // top
            edge = 0;
        } else if (position.x >= size - 32) {
            // right
            edge = 1;
        } else if (position.y >= size - 32) {
            // bottom
            edge = 2;
        } else if (position.x <= 0) {
            // left
            edge = 3;
        }

        _game->switchRoom(edge);
    }

    return exit;
}


/**
 * Updates the player every frame.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Player::_update(const UpdateState &us) {
	Vector2 direction;
	if (_game->getMove()->getDirection(direction)) {
		Vector2 position = getPosition();
        direction = correctDirection( position, direction );
        _setFacing(direction);
		position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!

        if (!_isExit(position)) {
            setPosition(position);
        }
    }
}
