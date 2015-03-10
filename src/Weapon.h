#pragma once

#include <stdio.h>

#include "Thing.h"

DECLARE_SMART(Weapon, spWeapon);
class Weapon: public Thing {
    
public:
    Weapon(int weaponType);
    
    /**
     *  Gets bounds of the unit Weapon.
     *  @return: SDL_Rect which is the bounds of Weapon.
     */
    SDL_Rect getBounds();
    
    /**
     * Adds sprite and attachs it to the game.
     */
    virtual void addSprite();
    
private:
    int _value;
    int _weaponType;
    
    /**
     * Initializes a Weapon position and sprite. Called by Unit's init() method.
     */
    void _init();
    
    /**
     *  Adds Weapon to the player's current attack stat.
     *  Removes sprite from the game.
     */
    void _interact();
    
    /**
     * Updates the Weapon every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};