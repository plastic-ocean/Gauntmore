//
//  pathFinding.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include <cmath>
#include "pathFinder.h"
#include "game.h"
#include "pathNode.h"

/*
        basic implementation of A* pathfinding algorithm
 
 1. calculate heuristic from target to current node using manhattan method. This will create an inadmissible heuristic
 but we are more concerned with fast pathfinding, not the shortest possible path
 
 
 3. build a min-heap of adjacent nodes using the Total Expected cost (distance travelled from start point + estimated remaining distance via heuristic)
 
 4. Once target is hit, follow chain of pointers back to start, storing each location in a stack.
 
 5. Pop stack into tweenQueue and fire animation
 
 
 
 */

int pathFinder::findHeuristic( pathNode curNode ) {
    Vector2 curLoc = curNode.getLocation();
    return abs( curLoc.x - this->target.x ) + abs( curLoc.y - this->target.y );
}