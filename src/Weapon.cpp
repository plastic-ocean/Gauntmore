//
//  Weapon.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 3/3/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "Weapon.h"
#include "res.h"
#include "game.h"
#include "Player.h"

/**
 *  Constructor.
 */
Weapon::Weapon(int weaponType):_value(weaponType) {
    _weaponType = weaponType;
    setType("weapon");
}

/**
 *  Gets bounds of the unit Gold.
 *  @return: SDL_Rect _bounds which is the bounds of Gold.
 */
SDL_Rect Weapon::getBounds() {
    Vector2 unitPosition = getPosition();
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    return _bounds;
}

/**
 * Adds sprite and attachs it to the game.
 */
void Weapon::addSprite() {
    _sprite = new Sprite;
    
    switch (_weaponType) {
        case 2:
            _sprite->setResAnim(resources.getResAnim("weapon2"));
            break;
        case 3:
            _sprite->setResAnim(resources.getResAnim("weapon3"));
            break;
        default:
            break;
    }
    
    
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}

/**
 *  Method to determine whether unit is a Potion.
 *  @returns false since the current unit is Weapon.
 */
bool Weapon::isPotion() {
    return false;
}

/**
 * Initializes a Weapon position and sprite. Called by Unit's init() method.
 */
void Weapon::_init() {
    addSprite();
}

/**
 *  Adds Weapon to the player.
 *  Removes sprite from the game.
 */
void Weapon::_interact() {
    if (!isDead()) {
        _game->getPlayer()->setAttack(_value);
        _game->updateWeaponCount(_value);
        
        /* Removes Sprite from game */
        _view->addTween(Actor::TweenAlpha(0), 1500)->setDetachActor(true);
        _dead = true;
    }
}

/**
 * Updates Weapon every frame. Called by Units update() method.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Weapon::_update(const UpdateState &us) {
    
}