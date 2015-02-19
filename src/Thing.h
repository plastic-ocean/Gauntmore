//
//  Thing.h
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/12/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__Thing__
#define __gauntmore_macosx__Thing__

#include <stdio.h>
#include "Unit.h"

DECLARE_SMART(Thing, spThing);
class Thing: public Unit {
    
public:
    Thing();
    
    /**
     * Interaction method for Thing.
     * Method is Virtual and will be defined elsewhere.
     */
    virtual void interact();
    
protected:
    
    bool _open;
    
    /**
     * Initializes position and sprite of Thing. Called by Unit's init() method.
     */
    void _init();
    
    
    
    /**
     * Updates the Thing every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore_macosx__Thing__) */
