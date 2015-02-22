#ifndef __gauntmore__pathNode__
#define __gauntmore__pathNode__

#include "Map.h"
#include "Creature.h"
#include "Game.h"

class PathNode {
public:
    PathNode( Vector2, int, int );
    ~PathNode();
    Vector2 getLocation();
    int getHeuristic();
    int getCost();
    const int getTotal();
    void setHeuristic(int);
    void setCost(int);
    void calculateTotal();
    void setLocation(Vector2);
//    bool operator >(  pathNode& node );
    PathNode getParent();
    void setParent(PathNode);
    
private:
    Vector2 location;
    int heuristic; //estimated cost from current to target
    int cost; //current cost from start to target
    int total; //cost + heuristic
    PathNode *parent;//not Java, pointers are not universal
    
    
    
    
};




#endif /* defined(__gauntmore_macosx__pathNode__) */
