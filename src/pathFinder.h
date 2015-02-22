#ifndef __gauntmore__pathFinder__
#define __gauntmore__pathFinder__

#include "Game.h"
#include "Map.h"
#include "PathNode.h"
//#include "GreaterThan.h"


class PathFinder {
    
    
public:
    PathFinder( Vector2, Vector2 );
    ~PathFinder();
    int findHeuristic( Vector2 );
    void aStar();                       //***  what should this return?  ***
    
    
    
    
private:
    Vector2 target;
    Vector2 location;
//    std::priority_queue<pathNode,vector<pathNode>, GreaterThan> openList;
    vector<PathNode> closedList;
    int mapSize = 64;   //*** FIX ME ***
    
    
};

#endif /* defined(__gauntmore_macosx__pathFinder__) */
