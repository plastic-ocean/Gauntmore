//#pragma once
//#include "oxygine-framework.h"
//#include "PathNode.h"
//
//#include "NodeMinHeap.h"
//#include "Game.h"
//#include "Map.h"
//#include "PathNode.h"
//
//
//using namespace oxygine;
//using namespace std;
//
////class NodeMinHeap;
////class PathNode;
//DECLARE_SMART(PathFinder, spPathFinder);
//class PathFinder : public Object {
//
//public:
//    PathFinder();
//    ~PathFinder();
//    int findHeuristic( Vector2 );
//    vector<Vector2> aStar( Vector2, Vector2 );                       //***  what should this return?  ***
//
//private:
//    Vector2 target;
//    Vector2 source;
//    NodeMinHeap* openList;
//    vector<PathNode> closedList;
//    int mapSize = 64;   //*** FIX ME ***
//    void scanSurround( PathNode node );
//    bool inClosedList( PathNode node );
//    bool atExit( PathNode );
//    vector<Vector2> makePath(PathNode);
//
//};
