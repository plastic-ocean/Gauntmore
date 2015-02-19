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
//#include "GreaterThan.h"


class pathFinder {
    
    
public:
    pathFinder( Vector2, Vector2 );
    ~pathFinder();
    int findHeuristic( Vector2 );
    void aStar();                       //***  what should this return?  ***
    
    
    
    
private:
    Vector2 target;
    Vector2 location;
//    std::priority_queue<pathNode,vector<pathNode>, GreaterThan> openList;
    vector<pathNode> closedList;
    int mapSize = 64;   //*** FIX ME ***
    
    
};

#endif /* defined(__gauntmore_macosx__pathFinder__) */
