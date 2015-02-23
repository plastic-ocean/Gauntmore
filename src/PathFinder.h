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
#include "NodeMinHeap.h"
#include "Game.h"
#include "Map.h"
#include "PathNode.h"
#include "GreaterThan.h"

class NodeMinHeap;
class PathNode;
DECLARE_SMART(PathFinder, spPathFinder);
class PathFinder : public Object {
    
    
public:
    PathFinder();
    ~PathFinder();
    int findHeuristic( Vector2 );
    vector<Vector2> aStar( Vector2, Vector2 );                       //***  what should this return?  ***
    
    
    
    
private:
    Vector2 target;
    Vector2 source;
    NodeMinHeap* openList;
    vector<PathNode> closedList;
    int mapSize = 64;   //*** FIX ME ***
    void scanSurround( PathNode node );
    bool inClosedList( PathNode node );
    bool atExit( PathNode );
    vector<Vector2> makePath(PathNode);
    
    
};

#endif /* defined(__gauntmore_macosx__PathFinder__) */
