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
        
        scanSurround( &temp );//add surrounding nodes to open list
    }
    
    //if you got here, there is no path to the target.
    return noMove;
    
}

void PathFinder::addNode(PathNode *node) {
    closedList[loc++] = *node;
}



int PathFinder::findHeuristic( Vector2 curLoc ) {
    int temp = abs( curLoc.x - this->target.x ) + abs( curLoc.y - this->target.y );
    if ( coll.detectWalls(_game->getTiles(), (int)curLoc.x, (int)curLoc.y, 64, 64) ) return 99999;
    
    return temp;
}


void PathFinder::scanSurround( PathNode *node ) {
    Vector2 temp = node->getLocation();
    temp.x -= mapSize;
    temp.y -= mapSize;
    int summ = 12;//something more clever goes here
    int flip = -2;
    
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            flip *= (-1);

            if (temp.x > 0 && temp.y > 0 ) {//is the location > 0?
            PathNode nodeNew = PathNode( temp, node->getCost()+(summ+flip), findHeuristic(temp), &closedList[loc-1] );
                
                if (!inClosedList(nodeNew) && nodeNew.getCost() < 99999 ) {
                    
                            openList.insertNode(&nodeNew);
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


Vector2 PathFinder::setDirection(Vector2 cPos) {
    Vector2 moveDir = {0,0};
    
    Vector2 pPos = _game->getPlayer()->getPosition();//player's position

    if ( abs(pPos.x - cPos.x) <= 50 && abs(pPos.y - cPos.y) <= 50 ) {
        return moveDir;//you are less than 50 pixels away, do nothing
    }
    //otherwise, check the movement Queue
    if ( moveQ.empty() ) {
        moveQ = aStar(cPos, pPos);
        return moveDir;
    }
    //if the Q is NOT empty
    Vector2 nextSpot = moveQ.back();//look at where you are going
    if ( abs(cPos.x - nextSpot.x) <= 9 && abs(cPos.y - nextSpot.y) <= 9) {
        moveQ = aStar(nextSpot, pPos);
    }
    
    
    if ( (cPos.x - nextSpot.x) < -4  ) {
            moveDir.x = 1;//move right
    }
    else if ( (cPos.x - nextSpot.x) > 4 ) {
          moveDir.x = -1;//move left
    }
    if ( (cPos.y - nextSpot.y) < -4  ) {
            moveDir.y = 1;//move down
    }
    else if ( (cPos.y - nextSpot.y) > 4 ) {
            moveDir.y = -1;//move up
    }
    
    return fixDirection(cPos, moveDir);

}
Vector2 PathFinder::fixDirection(Vector2 position, Vector2 direction) {
    int newX = position.x + (direction.x * 5);
    int newY = position.y + (direction.y * 5);
    
    if ( coll.detectWalls(_game->getTiles(), newX, position.y, 30, 30) ) {
        direction.x = 0;
    }
    if ( coll.detectWalls(_game->getTiles(), position.x, newY, 32, 32) ) {
        direction.y = 0;
    }
 
    return direction;
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
