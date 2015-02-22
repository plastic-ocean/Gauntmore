#include <cmath>
#include "pathFinder.h"
#include "game.h"
#include "pathNode.h"

/*
        basic implementation of A* pathfinding algorithm
 
 1. calculate heuristic from target to current node using manhattan method. This will create an inadmissible heuristic
 but we are more concerned with fast pathfinding, not the shortest possible path
 
 
 2. build a min-heap of adjacent nodes using the Total Expected cost (distance travelled from start point + estimated remaining distance via heuristic)
 
 3. Once target is hit, follow chain of pointers back to start, storing each location in a stack.
 
 4. Pop stack into tweenQueue and fire animation
 
 
 
 */
PathFinder::PathFinder(Vector2 start, Vector2 finish ) {
    this->location = start;
    this->target = finish;
    
}

void PathFinder::aStar() {
    PathNode start = *new PathNode( location, 0, findHeuristic(location) );
    
//    openList.push(start);
//    while ( !openList.empty() ) {
//        //do things here
//    }
    
    
}

int PathFinder::findHeuristic( Vector2 curLoc ) {
    return abs( curLoc.x - this->target.x ) + abs( curLoc.y - this->target.y );
}



