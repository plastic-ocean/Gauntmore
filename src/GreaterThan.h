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
