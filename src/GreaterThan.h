<<<<<<< HEAD
////
////  GreaterThan.h
////  gauntmore_macosx
////
////  Created by David Wenzel on 2/18/15.
////  Copyright (c) 2015 oxygine. All rights reserved.
////
//
//#ifndef __gauntmore_macosx__GreaterThan__
//#define __gauntmore_macosx__GreaterThan__
//#include "PathNode.h"
//#include "PathFinder.h"
//#include "Game.h"
//
//class PathNode;
//class GreaterThan {
//public:
//    bool operator()( PathNode &a, PathNode &b ){return a.getCost() > b.getCost(); }
//    
//};
//
//#endif /* defined(__gauntmore_macosx__GreaterThan__) */
=======
#ifndef __gauntmore__GreaterThan__
#define __gauntmore__GreaterThan__

#include "PathNode.h"
#include "PathFinder.h"
#include "Game.h"

#include <stdio.h>

class GreaterThan {
public:
    bool operator()( PathNode &a, PathNode &b ){return a.getCost() > b.getCost(); }
    
};

#endif /* defined(__gauntmore__GreaterThan__) */
>>>>>>> origin/keith
