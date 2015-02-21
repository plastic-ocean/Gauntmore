//
//  PathFinder.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__PathFinder__
#define __gauntmore_macosx__PathFinder__

#include <stdio.h>
#include <queue>
#include "Game.h"
#include "Map.h"
#include "pathNode.h"
#include "GreaterThan.h"


class PathFinder {
    
    
public:
    PathFinder();
    ~PathFinder();
    int findHeuristic( Vector2 );
    vector<Vector2> aStar( Vector2, Vector2 );                       //***  what should this return?  ***
    
    
    
    
private:
    Vector2 target;
    Vector2 source;
    std::priority_queue< pathNode, vector<pathNode>, GreaterThan > openList;
    vector<pathNode> closedList;
    int mapSize = 64;   //*** FIX ME ***
    void scanSurround( pathNode node );
    bool inClosedList( pathNode node );
    bool atExit( pathNode );
    vector<Vector2> makePath(pathNode);
    
};

#endif /* defined(__gauntmore_macosx__PathFinder__) */
