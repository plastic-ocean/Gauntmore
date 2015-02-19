//
//  Gold.h
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/16/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__Gold__
#define __gauntmore_macosx__Gold__

#include <stdio.h>
#include "Thing.h"
#include "Unit.h"

DECLARE_SMART(Gold, spGold);
class Gold: public Thing {
    
public:
    Gold();
    
    /**
     * Interaction method for Gold.
     */
    void interact();
    
private:
    /**
     * Initializes position and sprite of Gold. Called by Unit's init() method.
     */
    void _init();
    
    
    
    /**
     * Updates the Gold every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore_macosx__Gold__) */
