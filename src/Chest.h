//
//  Chest.h
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/13/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__Chest__
#define __gauntmore_macosx__Chest__

#include <stdio.h>
#include "Thing.h"
#include "Unit.h"

using namespace std;

enum Things {potion, gold};

DECLARE_SMART(Chest, spChest);
class Chest: public Thing {
    
public:
    Chest();
    
    /**
     * Interaction method for Chest.
     */
    void interact();
    
//    vector<spThing> getContents() {
//        return _contents;
//    }s
//    
//    void pushContents(spThing thing) {
//        _contents.push_back(thing);
//    }
    
private:
//    vector<spThing> _contents;
    int _contents;
    
    void _chooseContents();
    
    /**
     * Initializes position and sprite of Chest. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Updates the Chest every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore_macosx__Chest__) */
