#include <iostream>

#include "Player.h"
#include "Game.h"
#include "Thing.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Map.h"
#include "HealthBar.h"
#include "Room.h"


/**
 * Constructor.
 */
Player::Player(int hp, int attack, int defense):_hasTween(false), _facing(down) {
    _collisionDetector = new CollisionDetector(_game);
    setType("player");
    
    _hp = hp;
    _attack = attack;
    _defense = defense;
}



/**
 * Initializes the player's position and sprite. Called by Unit's init() method.
 */
void Player::_init() {
    addSprite();
}


Player::Facing Player::getFacing() {
    return _facing;
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
    }
}


/**
 * Interacts with Things or Creatures.
 * Iterates through every unit on the current map and sees if the user
 * is in interacting distance with it based off what direction they are facing.
 * Depending on what the unit is infront of us (monster, chest, etc) we will
 * call a different method (damage, open, etc)
 *
 * Gets the position of the user and the unit, takes the difference of
 * their positions and determines if we are in interacting distance.
 */
void Player::interact() {
    attack();
    
    Vector2 playerPosition = getPosition();
    std::list<spUnit> units = _game->getUnits();

    for (spUnit unit : units) {
        Vector2 unitPosition = unit->getPosition();
//        int yDiff = playerPosition.y - unitPosition.y;
//        int xDiff = playerPosition.x - unitPosition.x;
//        std::cout << "yDiff: " << yDiff << std::endl;
//        std::cout << "xDiff: " << xDiff << std::endl;
        
        SDL_Rect rect;
        SDL_Rect otherRect = unit->getBounds();

        switch(_facing){
            case up:
                rect.x = playerPosition.x;
                rect.y = playerPosition.y + 16;
                rect.h = 16;
                rect.w = 64;
                if (_isCollision(rect, unit)) {
                    std::cout << "interact facing up " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
            case right:
                rect.x = playerPosition.x + 80;
                rect.y = playerPosition.y;
                rect.h = 64;
                rect.w = 64;
                if (_isCollision(rect, unit)) {
                    std::cout << "interact facing right " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
            case down:
                rect.x = playerPosition.x;
                rect.y = playerPosition.y - 80;
                rect.h = 16;
                rect.w = 64;
                if (_isCollision(rect, unit)) {
                    std::cout << "interact facing down " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
            case left:
                rect.x = playerPosition.x - 16;
                rect.y = playerPosition.y;
                rect.h = 64;
                rect.w = 16;
                if (_isCollision(rect, unit)) {
                    std::cout << "interact facing left " << i << std::endl;
                    unit->interact();
                    i++;
                }
                break;
            default:
                break;
        }
        
    }
    
}


/**
 * Adds the player sprite to the map.
 */
void Player::addSprite() {
    _sprite = new Sprite;
//    _sprite->setScale(1.25f);
    _sprite->setResAnim(resources.getResAnim("adventurer_move_down"));
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    _sprite->attachTo(_view);
}


/**
 * Plays the attack animation.
 */
void Player::attack() {
    switch (_facing) {
        case up:
            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_up")), 300);
            break;
        case right:
            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_right")), 300);
            break;
        case down:
            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_down")), 300);
            break;
        case left:
            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_attack_left")), 300);
            break;
        default:
            break;
    }
}


/**
 * Plays the move animation.
 */
void Player::move(int facing) {
    _facing = static_cast<Facing>(facing);
    _checkTween();
    switch (_facing) {
        case up:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_up")), 500, -1);
            break;
        case right:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_right")), 500, -1);
            break;
        case down:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_down")), 500, -1);
            break;
        case left:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("adventurer_move_left")), 500, -1);
            break;
        default:
            break;
    }
    
}


void Player::removeTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
    }
    _hasTween = false;
}


void Player::_checkTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
    }
    _hasTween = true;
}


//void Player::_setFacing(Vector2 dir) {
//    if ( dir.y > 0 ) {
//        _sprite->setResAnim(resources.getResAnim("adventurer_move_down"));
//        _facing = down;
//    }
//    if ( dir.y < 0 ) {
//        _sprite->setResAnim(resources.getResAnim("adventurer_move_up"));
//        _facing = up;
//    }
//    if ( dir.x < 0 ) {
//        _sprite->setResAnim(resources.getResAnim("adventurer_move_left"));
//        _facing = left;
//    }
//    if ( dir.x > 0 ) {
//        _sprite->setResAnim(resources.getResAnim("adventurer_move_right"));
//        _facing = right;
//    }
//}


/**
 * Corrects the movement direction by checking for collision with wall tiles or other Units and adjusting the 
 * direction vector's x and y values.
 *
 * @postion is the player's current position.
 * @directions is the player's current movement direction.
 */
Vector2 Player::_correctDirection(Vector2 position, Vector2 direction) {
    int newX = static_cast<int>(position.x) + static_cast<int>(direction.x) * 5;
    int newY = static_cast<int>(position.y) + static_cast<int>(direction.y) * 5;
    
    SDL_Rect spriteRect;
    spriteRect.x = newX + 10;
    spriteRect.y = newY + 12;
    spriteRect.h = tileSize - 14;
    spriteRect.w = tileSize - 24;
    
    if (_collisionDetector->detectWalls(_game->getTiles(), spriteRect) ||
        _collisionDetector->detectUnits(_game->getUnits(), spriteRect)) {
        direction.x = 0;
    }
    if (_collisionDetector->detectWalls(_game->getTiles(), spriteRect) ||
        _collisionDetector->detectUnits(_game->getUnits(), spriteRect)) {
        direction.y = 0;
    }
    
    return direction;
}


bool Player::_isCollision(SDL_Rect thisRect, spUnit unit) {
    bool isCollision = false;
    SDL_Rect otherRect = unit->getBounds();
    const SDL_Rect *playerRect = &thisRect;
    const SDL_Rect *unitRect = &otherRect;
    if (SDL_HasIntersection(playerRect, unitRect)) {
        std::cout << "interact facing up " << i << std::endl;
        unit->interact();
        i++;
        isCollision = true;
    }
    
    return isCollision;
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
        direction = _correctDirection( position, direction );
//        _setFacing(direction);
		position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!

        if (!_game->isExit(position)) {
            setPosition(position);
        }
    }
}


