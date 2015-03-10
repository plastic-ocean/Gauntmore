#ifndef __gauntmore_macosx__PathFinder__
#define __gauntmore_macosx__PathFinder__

#include <cmath>
#include <stdio.h>
#include <queue>
#include "NodeMinHeap.h"
#include "PathNode.h"
#include "CollisionDetector.h"
#include "Game.h"

class Game;
class PathFinder : public Object {
public:
    PathFinder();
    
    PathFinder(Game *game);
    
    ~PathFinder();
    
    /*
     Sets the game, called in _init() for creature
     */
    
    void setGame(Game *game);
    
    /*
     A* algorithm main method @start is location of Creature, @finish is location of Player
     */
    
    vector<Vector2> aStar( Vector2, Vector2 );
    
    /*
     Calculates the 'expected' cost from the creature to the player
     @curLoc is the current location of the Creature
     */
    
    int findHeuristic( Vector2 );
    
    /*
     Determines which direction Creature needs to move to get to the next 'breadcrumb'
     @cPos is the current location of the Creature
     */
    
    Vector2 setDirection(Vector2);
    
    
private:
    const static int _TILESIZE = 64;
    const static int _MAPBOUND = 768;
    int _loc;
    
    Game *_game;
    CollisionDetector _coll;
    
    vector<Vector2> _moveQ;
    Vector2 _target;
    Vector2 _source;
    
    NodeMinHeap _openList;
    PathNode _closedList[1000];
    
    /*
     Looks at the 8 squares surrounding the current node
     @node is the current location that A* is looking at.
     */
    
    void _scanSurround( PathNode *node );
    
    /*
     Checks to see if node is near the end
     @node is the current node A* is looking at
     */
    
    bool _atExit( PathNode );
    
    /*
     Forces Creature to not walk into walls
     @position is the current location of Creature
     @direction is the Vector2 we would like to apply
     */
    
    Vector2 _fixDirection(Vector2, Vector2);
    
    /*
     Searches the closed list for a node
     @node is the location being looked at
     */
    
    bool _inClosedList( PathNode node );
    
    /*
     Takes a node, and follows it's parents to the start, storing each location in a stack, then returns that stack of Vector2 'breadcrumbs'
     @node is the location near the Player
     */
    
    std::vector<Vector2> _makePath(PathNode);
   
    
    
};

#endif /* defined(__gauntmore_macosx__PathFinder__) */
