//
//  CreatureMover.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/24/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__CreatureMover__
#define __gauntmore_macosx__CreatureMover__

#include <stdio.h>
#include "Game.h"
#include "PathFinder.h"


class CreatureMover {
public:
    CreatureMover();
    ~CreatureMover();
    bool updatePath(vector<Vector2>);
    Vector2 nextMove();
    
private:
    vector<Vector2> thePath;
    
    
};




#endif /* defined(__gauntmore_macosx__CreatureMover__) */
