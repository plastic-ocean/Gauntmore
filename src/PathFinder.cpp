#include <queue>
#include <cmath>
#include "PathFinder.h"
#include "Game.h"
#include "PathNode.h"

/*
        basic implementation of A* pathfinding algorithm
 
 1. calculate heuristic from target to current node using manhattan method. This will create an inadmissible heuristic
 but we are more concerned with fast pathfinding, not the shortest possible path
 
 
 2. build a min-heap of adjacent nodes using the Total Expected cost (distance travelled from start point + estimated remaining distance via heuristic)
 
 3. Once target is hit, follow chain of pointers back to start, storing each location in a stack.
 
 4. Pop stack into tweenQueue and fire animation
 
 
 
 */
PathFinder::PathFinder():loc(0) {}

PathFinder::PathFinder(Game *game):_game(game) {
    loc = 0;
}

PathFinder::~PathFinder() {
    
}
void PathFinder::setGame( Game *game ) {
    _game = game;
}

vector<Vector2> PathFinder::aStar(Vector2 start, Vector2 finish ) {
    PathNode *first =  new PathNode( start, 0, 0 );
    openList.clearHeap();
    target = finish;
    source = start;
    loc = 0;
    vector<Vector2> noMove;
    noMove.push_back(source);
    
    openList.insertNode(first);//add start to heap
    
    while ( !openList.empty() ) {
        if (openList.getSize() > 999 || loc > 999 ) return noMove;
        PathNode temp = openList.getMinNode();//pop smallest from heap
        if ( atExit(temp) ) {//are we at the exit?
           return makePath(temp);
            
        }
        closedList[loc++] = temp;
//        addNode( &temp );//put node in closed list
        
        scanSurround( &temp );//add surrounding nodes to open list
    }
    
    //if you got here, there is no path to the target.
    return noMove;
    
}

void PathFinder::addNode(PathNode *node) {
    closedList[loc++] = *node;
}



int PathFinder::findHeuristic( Vector2 curLoc ) {
    return abs( curLoc.x - this->target.x ) + abs( curLoc.y - this->target.y );
}


void PathFinder::scanSurround( PathNode *node ) {
    Vector2 temp = node->getLocation();
    Vector2 old = node->getLocation();
    temp.x -=(int) mapSize;
    temp.y -=(int) mapSize;
    int summ = 12;//something more clever goes here
    int flip = -2;
    bool insert = false;
    
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            flip *= (-1);

            if (temp.x > 0 && temp.y > 0 ) {//is the location > 0?
            PathNode nodeNew = PathNode( temp, node->getCost()+(summ+flip), findHeuristic(temp), &closedList[loc-1] );
                
                if (!inClosedList(nodeNew) ) {
                    
                    if (flip < 0) {//Cardinal collision detection
                        if ( !coll.detectWalls(_game->getTiles(), temp.x, temp.y, 50, 50) ) {
                            openList.insertNode(&nodeNew);
                            
                        }
                    } else {//diagonal collision detection
//                        insert = true; //set flag
//                        old -= temp;
//                        
//                        if ( old.x > 0 && coll.detectWalls(_game->getTiles(), temp.x + 50, temp.y, 50, 50) ) insert = false;
//                        if ( old.x < 0 && coll.detectWalls(_game->getTiles(), temp.x - 50, temp.y, 50, 50) ) insert = false;
//                        if ( old.y > 0 && coll.detectWalls(_game->getTiles(), temp.x, temp.y + 50, 50, 50) ) insert = false;
//                        if ( old.y < 0 && coll.detectWalls(_game->getTiles(), temp.x, temp.y - 50, 50, 50) ) insert = false;
//                        if ( insert == true ) openList.insertNode(&nodeNew);
//                        insert = false; 
                    }
                  
                }
            }
            
            temp.x += mapSize;
        }
        temp.x -= (3*mapSize);
        temp.y += mapSize;
    }

    
}
bool PathFinder::atExit( PathNode node ) {
    Vector2 location = node.getLocation();
    int fudge = 64;
    int diffX = abs( location.x - target.x );
    int diffY = abs( location.y - target.y );
    
    if (diffX <= fudge && diffY <= fudge ) return true;
    return false;
}



bool PathFinder::inClosedList( PathNode node ) {
    int size = loc;
    for (int i = 0; i<size;i++ ) {
        if ( closedList[i].getLocation() == node.getLocation() ) return true;
    }
    return false;
    
}

vector<Vector2> PathFinder::makePath(PathNode node ) {
    
    vector<Vector2> tempVect;

    while (node.getLocation() != source ) {
        tempVect.push_back( node.getLocation() );
        node = *node.getParent();
        }
    return tempVect;
}
