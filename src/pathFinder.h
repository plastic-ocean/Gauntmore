//
//  pathFinder.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__pathFinder__
#define __gauntmore_macosx__pathFinder__

#include <stdio.h>
#include <queue>
#include "Game.h"
#include "Map.h"
#include "pathNode.h"

#endif /* defined(__gauntmore_macosx__pathFinder__) */

class pathFinder {
public:
    pathFinder(Vector2 location, Vector2 target);
    
    int findHeuristic( pathNode curNode );
    void aStar();                       //***  what should this return?  ***
    
    
    
    
private:
    Vector2 target;
    Vector2 location;
    std::priority_queue<pathNode, vector<pathNode>, std::greater<pathNode> > openList;
    vector<pathNode> closedList;

    
};