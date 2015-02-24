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
    _collisionDetector = new CollisionDetector();
    setType("player");
    
    _hp = hp;
    _maxHealth = hp;
    _attack = attack;
    _defense = defense;
}


/**
 * Get the bounds used for collision detection.
 */
SDL_Rect Player::getBounds() {
    SDL_Rect spriteRect;
    spriteRect.x += 10;
    spriteRect.y += 12;
    spriteRect.h = tileSize - 14;
    spriteRect.w = tileSize - 24;
    return spriteRect;
}


/**
 * Get the current facing.
 */
Player::Facing Player::getFacing() {
    return _facing;
}


/**
 * Updates the player's health.
 *
 * @health is the number to add to _hp.
 * @return true if it was updated, false if it was not.
 */
bool Player::updateHealth(int health) {
    bool isUpdated = false;
    
    if (_hp + health < _maxHealth) {
        _hp += health;
        
        // Convert health to a decimal percentage for the health bar.
        float healthPercent = health * 0.1;
        if (healthPercent > 1.0) {
            healthPercent = 1.0;
        }
        
        _game->updateHealth(healthPercent);
        
        isUpdated = true;
    }
    
    if (_hp <= 0) {
        // The player is dead, hide it with an alpha tween.
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dead = true;
    }
    
    return isUpdated;
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
    std::list<spUnit> *units = _game->getMap()->getRoom()->getUnits();

    for (spUnit unit : *units) {
        SDL_Rect rect;

        switch(_facing) {
            case up:
                rect.x = playerPosition.x;
                rect.y = playerPosition.y - 16;
                rect.h = 16;
                rect.w = 64;
                if (_isCollision(rect, unit)) {
                    unit->interact();
                }
                break;
            case right:
                rect.x = playerPosition.x + 64;
                rect.y = playerPosition.y;
                rect.h = 64;
                rect.w = 64;
                if (_isCollision(rect, unit)) {
                    unit->interact();
                }
                break;
            case down:
                rect.x = playerPosition.x;
                rect.y = playerPosition.y + 64;
                rect.h = 16;
                rect.w = 64;
                if (_isCollision(rect, unit)) {
                    unit->interact();
                }
                break;
            case left:
                rect.x = playerPosition.x - 16;
                rect.y = playerPosition.y;
                rect.h = 64;
                rect.w = 16;
                if (_isCollision(rect, unit)) {
                    unit->interact();
                }
                break;
            default:
                break;
        }
        
    }
    
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


/**
 * Remove the tween from the sprite.
 */
void Player::removeTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
    }
    _hasTween = false;
}


/**
 * Adds the player sprite to the map.
 */
void Player::addSprite() {
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("adventurer_move_down"));
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    _sprite->attachTo(_view);
}

bool Player::isDamaged() {
    return  _hp != _maxHealth;
}


/**
 * Initializes the player's position and sprite. Called by Unit's init() method.
 */
void Player::_init() {
    addSprite();
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
        direction = _correctDirection(position, direction);
        position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
        
        if (!_game->isExit(position)) {
            setPosition(position);
        }
    }
}


/**
 * Checks whether the sprite already has a tween before trying to removing it.
 */
void Player::_checkTween() {
    if (_hasTween) {
        _sprite->removeTween(_moveTween);
    }
    _hasTween = true;
}


/**
 * Checks for a collision between the players rect and the unit's rect.
 *
 * @rect is an SDL_Rect for the player.
 * @unit is the unit to check against.
 */
bool Player::_isCollision(SDL_Rect thisRect, spUnit unit) {
    bool isCollision = false;
    SDL_Rect otherRect = unit->getBounds();
    const SDL_Rect *playerRect = &thisRect;
    const SDL_Rect *unitRect = &otherRect;
    
    if (SDL_HasIntersection(playerRect, unitRect)) {
        unit->interact();
        isCollision = true;
    }
    
    return isCollision;
}


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
        _collisionDetector->detectUnits(_game->getMap()->getRoom()->getUnits(), spriteRect)) {
        direction.x = 0;
    }
    if (_collisionDetector->detectWalls(_game->getTiles(), spriteRect) ||
        _collisionDetector->detectUnits(_game->getMap()->getRoom()->getUnits(), spriteRect)) {
        direction.y = 0;
    }
    
    return direction;
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


