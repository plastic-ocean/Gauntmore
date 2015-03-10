//
//  Armor.h
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/26/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__Armor__
#define __gauntmore_macosx__Armor__

#include <stdio.h>

#include "Thing.h"

DECLARE_SMART(Armor, spArmor);
class Armor: public Thing {
    
public:
    Armor(int armorType);
    
    /**
     *  Gets bounds of the unit Armor.
     *  @return: SDL_Rect which is the bounds of Armor.
     */
    SDL_Rect getBounds();
    
    /**
     * Adds sprite and attachs it to the game.
     */
    virtual void addSprite();
    
private:
    int _value;
    int _armorType;
    
    /**
     * Initializes a Armor position and sprite. Called by Unit's init() method.
     */
    void _init();
    
    /**
     *  Adds Armor to the player's current defense stat.
     *  Removes sprite from the game.
     */
    void _interact();
    
    /**
     * Updates the Armor every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore_macosx__Armor__) */
