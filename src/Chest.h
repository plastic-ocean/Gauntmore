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
#include "Potion.h"
#include "Gold.h"
#include "Unit.h"

using namespace std;

//enum Things {potion, gold};

DECLARE_SMART(Chest, spChest);
class Chest: public Thing {
    
public:
    Chest();
    
//    int getContents() {
//        return _contents;
//    }
//
//    void pushContents(spThing thing) {
//        _contents.push_back(thing);
//    }
    
private:
 //   vector<spThing> _contents;
    spThing _contents;
    
//    spPotion _potion;
//    spGold _gold;
//    spThing cont
    
    
    
    /**
     * Interaction method for Chest.
     */
    void _interact();

    
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
