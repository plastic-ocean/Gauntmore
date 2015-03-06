#ifndef __gauntmore_macosx__PathFinder__
#define __gauntmore_macosx__PathFinder__

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
    PathFinder(Game * game);
    ~PathFinder();
    int findHeuristic( Vector2 );
    vector<Vector2> aStar( Vector2, Vector2 );
    Vector2 nextMove(Vector2, Vector2);
    void setGame(Game *game);
    
private:
    Game *_game;
    Vector2 target;
    Vector2 source;
    NodeMinHeap openList;
    const static int mapSize = 64;   //*** FIX ME ***
    void scanSurround( PathNode *node );
    bool inClosedList( PathNode node );
    bool atExit( PathNode );
    std::vector<Vector2> makePath(PathNode);
    PathNode closedList[10000];
    void addNode(PathNode*);
    int loc;
    CollisionDetector coll;
    
    
};

#endif /* defined(__gauntmore_macosx__PathFinder__) */
