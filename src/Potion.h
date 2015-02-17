//
//  Potion.h
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/16/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__Potion__
#define __gauntmore_macosx__Potion__

#include <stdio.h>
#include "Thing.h"
#include "Unit.h"

DECLARE_SMART(Potion, spPotion);
class Potion: public Thing {
    
public:
    Potion();
    
    /**
     * Interaction method for Potion.
     */
    void interact();
    
private:
    /**
     * Initializes position and sprite of Potion. Called by Unit's init() method.
     */
    void _init();
    
    
    
    /**
     * Updates the Potion every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore_macosx__Potion__) */
