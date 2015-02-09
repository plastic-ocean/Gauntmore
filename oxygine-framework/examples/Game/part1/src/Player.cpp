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
        if (!detectCollision(pos.x, pos.y, 32, 32)) {
            _view->setPosition(pos);
        }
	}
}


/**
 * Detects collisions between the player and the walls.
 *
 * @x is the x coordinate to check.
 * @y is the y coordinate to check.
 * @h is the height coordinate to check.
 * @w is the width coordinate to check.
 * @return true if there is a collision and false if there is not
 */
bool Player::detectCollision(int x, int y, int h, int w) {
    bool isCollision = false;
    SDL_Rect spriteRect;
    spriteRect.x = x;
    spriteRect.y = y;
    spriteRect.h = h;
    spriteRect.w = w;
    
    // Iterate through the tiles vector to see if the spriteRect collides with the tile.
    const SDL_Rect *sprite = &spriteRect;
    std::vector<SDL_Rect> tiles = _game->getTiles();
    for (SDL_Rect tileRect : tiles) {
        const SDL_Rect *tile = &tileRect;
        if (SDL_HasIntersection(sprite, tile)) {
            isCollision = true;
        }
    }
    
    return isCollision;
}
