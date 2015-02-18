#include <iostream>

#include "Player.h"
#include "Game.h"
#include "Thing.h"
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

void Player::interact(){
    /*
     A method that goes through every unit on the map and sees if the user
     is in interacting distance with it based off what direction they are facing. 
     Depending on what the unit is infront of us (monster, chest, etc) we will
     call a different method (damage, open, etc)
     
     We basically get the position of the user and the unit, take the difference of
     their positions and based off that determine if we are in interacting distance.
    */
    
    Vector2 playerPosition = getPosition();
    std::list<spUnit> units = _game->getUnits();

    for (spUnit unit : units) {
        Vector2 unitPosition = unit->getPosition();
        int yDiff = playerPosition.y - unitPosition.y;
        int xDiff = playerPosition.x - unitPosition.x;
        //std::cout << "yDiff: " << yDiff << std::endl;
        //std::cout << "xDiff: " << xDiff << std::endl;

        switch(facing){
            case up:
                if((yDiff > -5 && yDiff < 15) && (xDiff > -26 && xDiff < 0)){
                    std::cout << "interact facing up " << i << std::endl;
                    //unit->damage();
                    i++;
                }
                break;
            case right:
                if((yDiff > -30 && yDiff < 0) && (xDiff < -30 && xDiff > -50)){
                    std::cout << "interact facing right " << i << std::endl;
                    i++;
                }
                break;
            case down:
                if((yDiff > -50 && yDiff < -25) && (xDiff > -26 && xDiff < 0)){
                    std::cout << "interact facing down " << i << std::endl;
                    i++;
                }
                break;
            case left:
                if((xDiff < 25 && xDiff > 0) && (yDiff > -30 && yDiff < 0)){
                    std::cout << "interact facing left " << i << std::endl;
                    i++;
                }
                break;
        }
        
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
    if ( dir.y > 0 ){
        _sprite->setResAnim(res::ui.getResAnim("player_front"));
        facing = down;
    }
    if ( dir.y < 0 ){
        _sprite->setResAnim(res::ui.getResAnim("player_back"));
        facing = up;
    }
    if ( dir.x < 0 ){
        _sprite->setResAnim(res::ui.getResAnim("player_left"));
        facing = left;
    }
    if ( dir.x > 0 ){
        _sprite->setResAnim(res::ui.getResAnim("player_right"));
        facing = right;
    }
}

void Player::moveUp() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(res::ui.getResAnim("player_move_back")), 300, -1);
}

void Player::moveDown() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(res::ui.getResAnim("player_move_front")), 300, -1);
}

void Player::moveRight() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(res::ui.getResAnim("player_move_right")), 300, -1);
}

void Player::moveLeft() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(res::ui.getResAnim("player_move_left")), 300, -1);
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
