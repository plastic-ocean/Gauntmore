#include <iostream>

#include "Player.h"
#include "Game.h"
#include "Thing.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Map.h"
#include "HealthBar.h"


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


Player::Facings Player::getFacing() {
    return facing;
}


/**
 * Reduces the player's hit points.
 */
void Player::damage() {
    _hp--;
    _game->updateHealth(0.05f); // TODO this float needs to reflect the percentage of total health that a single hit inflicts
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
                    unit->interact();
                    i++;
                }
                break;
            case right:
                if((yDiff > -30 && yDiff < 0) && (xDiff < -30 && xDiff > -50)){
                    std::cout << "interact facing right " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
            case down:
                if((yDiff > -50 && yDiff < -25) && (xDiff > -26 && xDiff < 0)){
                    std::cout << "interact facing down " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
            case left:
                if((xDiff < 25 && xDiff > 0) && (yDiff > -30 && yDiff < 0)){
                    std::cout << "interact facing left " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
        }
        
    }
    
}


Vector2 Player::correctDirection(Vector2 position, Vector2 direction) {
    int newX = static_cast<int>(position.x) + static_cast<int>(direction.x) * 5;
    int newY = static_cast<int>(position.y) + static_cast<int>(direction.y) * 5;
    
    if ( _game->detectCollision(newX, static_cast<int>(position.y), tileSize, tileSize ) ) direction.x = 0;
    if ( _game->detectCollision(static_cast<int>(position.x), newY, tileSize, tileSize ) ) direction.y = 0;
    
    return direction;
}


/**
 * Adds the player sprite to the map.
 */
void Player::addSprite() { 
    _sprite = new Sprite;
//    _sprite->setScale(1.25f);
    _sprite->setResAnim(resources.getResAnim("adventurer_down"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}



void Player::_setFacing(Vector2 dir) {
    if ( dir.y > 0 ) {
        _sprite->setResAnim(resources.getResAnim("adventurer_down"));
        facing = down;
    }
    if ( dir.y < 0 ) {
        _sprite->setResAnim(resources.getResAnim("adventurer_up"));
        facing = up;
    }
    if ( dir.x < 0 ) {
        _sprite->setResAnim(resources.getResAnim("adventurer_left"));
        facing = left;
    }
    if ( dir.x > 0 ) {
        _sprite->setResAnim(resources.getResAnim("adventurer_right"));
        facing = right;
    }
}


void Player::attack() {
    switch (facing) {
        case down:
            attackDown();
            break;
        case up:
            attackUp();
            break;
        case left:
            attackLeft();
            break;
        case right:
            attackRight();
            break;
        default:
            break;
    }
}


void Player::attackDown() {
    _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_down")), 300);
}


void Player::attackUp() {
    _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_up")), 300);
}


void Player::attackLeft() {
    _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_left")), 300);
}


void Player::attackRight() {
    _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_right")), 300);
}


void Player::moveUp() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_up")), 500, -1);
}


void Player::moveDown() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_down")), 500, -1);
}


void Player::moveRight() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_right")), 500, -1);
}


void Player::moveLeft() {
    _checkTween();
    _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_left")), 500, -1);
}


void Player::_checkTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
//        _sprite->removeTween(_attackTween);
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
    bool isExit = false;
    int size = _game->getMap()->getRoom()->getSize() * tileSize;

    if (!(position.x > 0 && position.x < size - tileSize && position.y > 0 && position.y < size - tileSize)) {
        isExit = true;
        int edge = 0;

        if (position.y <= 0) {
            // top
            edge = 0;
        } else if (position.x >= size - tileSize) {
            // right
            edge = 1;
        } else if (position.y >= size - tileSize) {
            // bottom
            edge = 2;
        } else if (position.x <= 0) {
            // left
            edge = 3;
        }

        _game->switchRoom(edge);
    }

    return isExit;
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


