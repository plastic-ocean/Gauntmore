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


/*
 Default Constructor
 */
PathFinder::PathFinder():_loc(0) {}


/*
 Overloaded Constructor
 */
PathFinder::PathFinder(Game *game):_game(game), _loc(0) {
}


/*
 Destructor
 */
PathFinder::~PathFinder() {
    
}


/*
 Sets the game, called in _init() for creature
 */
void PathFinder::setGame( Game *game ) {
    _game = game;
}


/*
 A* algorithm main method @start is location of Creature, @finish is location of Player
 */
vector<Vector2> PathFinder::aStar(Vector2 start, Vector2 finish ) {
    PathNode *first =  new PathNode( start, 0, 0 );
    _openList.clearHeap();
    _target = finish;
    _source = start;
    _loc = 0;
    vector<Vector2> noMove;
    noMove.push_back(_source);
    
    _openList.insertNode(first);//add start to heap
    
    while ( !_openList.empty() ) {
        if (_openList.getSize() > 999 || _loc > 999 ) return noMove;
        PathNode temp = _openList.getMinNode();//pop smallest from heap
        if ( _atExit(temp) ) {//are we at the exit?
           return _makePath(temp);
            
        }
        _closedList[_loc++] = temp;
        
        _scanSurround( &temp );//add surrounding nodes to open list
    }
    
    //if you got here, there is no path to the target.
    return noMove;
    
}


/*
 Calculates the 'expected' cost from the creature to the player
 @curLoc is the current location of the Creature
 */
int PathFinder::findHeuristic( Vector2 curLoc ) {
    int temp = abs( curLoc.x - this->_target.x ) + abs( curLoc.y - this->_target.y );
    if ( _coll.detect(_game->getTiles(), (int)curLoc.x+10, (int)curLoc.y+14, 48, 40) ) return 99999;
    
    return temp;
}


/*
 Looks at the 8 squares surrounding the current node
 @node is the current location that A* is looking at.
 */
void PathFinder::_scanSurround( PathNode *node ) {
    Vector2 temp = node->getLocation();
    temp.x -= _TILESIZE;
    temp.y -= _TILESIZE;
    int summ = 12;//something more clever goes here
    int flip = -2;
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            flip *= (-1);

            if (temp.x > 0 && temp.y > 0 ) {//is the location > 0?
            PathNode nodeNew = PathNode( temp, node->getCost()+(summ+flip), findHeuristic(temp), &_closedList[_loc-1] );
                
                if (!_inClosedList(nodeNew) && nodeNew.getCost() < 99999 ) {
                    
                            _openList.insertNode(&nodeNew);
                }
            }
            
            temp.x += _TILESIZE;
        }
        temp.x -= (3*_TILESIZE);
        temp.y += _TILESIZE;
    }

    
}


/*
 Checks to see if node is near the end
 @node is the current node A* is looking at
 */
bool PathFinder::_atExit( PathNode node ) {
    Vector2 location = node.getLocation();
    int fudge = 64;
    int diffX = abs( location.x - _target.x );
    int diffY = abs( location.y - _target.y );
    
    if (diffX <= fudge && diffY <= fudge ) return true;
    return false;
}


/*
 Determines which direction Creature needs to move to get to the next 'breadcrumb'
 @cPos is the current location of the Creature
 */
Vector2 PathFinder::setDirection(Vector2 cPos) {
    Vector2 moveDir = {0,0};
    
    Vector2 pPos = _game->getPlayer()->getPosition();//player's position

    if ( abs(pPos.x - cPos.x) <= 50 && abs(pPos.y - cPos.y) <= 50 ) {
        return moveDir;//you are less than 50 pixels away, do nothing
    }
    //otherwise, check the movement Queue
    if ( _moveQ.empty() ) {
        _moveQ = aStar(cPos, pPos);
        return moveDir;
    }
    //if the Q is NOT empty
    Vector2 nextSpot = _moveQ.back();//look at where you are going
    if ( abs(cPos.x - nextSpot.x) <= 9 && abs(cPos.y - nextSpot.y) <= 9) {
        _moveQ = aStar(nextSpot, pPos);
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
    
    return _fixDirection(cPos, moveDir);

}


/*
 Forces Creature to not walk into walls
 @position is the current location of Creature
 @direction is the Vector2 we would like to apply
 */
Vector2 PathFinder::_fixDirection(Vector2 position, Vector2 direction) {
    int newX = position.x + (direction.x * 5);
    int newY = position.y + (direction.y * 5);
    
    //this 'seems' to work now
    if ( _coll.detect(_game->getTiles(), newX+10, position.y+14, 1, 1) ) {
        direction.x = 0;
    }
    if ( _coll.detect(_game->getTiles(), position.x+10, newY+14, 1, 1) ) {
        direction.y = 0;
    }
 
    return direction;
}


/*
 Searches the closed list for a node
 @node is the location being looked at
 */
bool PathFinder::_inClosedList( PathNode node ) {
    int size = _loc;
    for (int i = 0; i < size; i++) {
        if ( _closedList[i].getLocation() == node.getLocation() ) return true;
    }
    return false;
    
}


/*
Takes a node, and follows it's parents to the start, storing each location in a stack, then returns that stack of Vector2 'breadcrumbs'
 @node is the location near the Player
 */
vector<Vector2> PathFinder::_makePath(PathNode node ) {
    
    vector<Vector2> tempVect;

    while (node.getLocation() != _source ) {
        tempVect.push_back( node.getLocation() );
        node = *node.getParent();
        }
    return tempVect;
}
