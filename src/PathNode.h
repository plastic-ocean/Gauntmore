#ifndef __gauntmore_macosx__PathNode__
#define __gauntmore_macosx__PathNode__

#include <stdio.h>
#include "Map.h"
#include "Game.h"

class PathNode {
public:
    PathNode();
    
    PathNode( Vector2, int, int );
    
    PathNode( Vector2, int, int, PathNode* );
    
    ~PathNode();
    
    /*
     getters and setters
     */
    
    const Vector2 getLocation();
    
    const int getHeuristic();
    
    const int getCost();
    
    const int getTotal();
    
    void setHeuristic(int);
    
    void setCost(int);
    
    void setLocation(Vector2);
    
    PathNode* getParent();
    
    void setParent(PathNode*);
    
private:
    Vector2 _location;
    int _heuristic; //estimated cost from current to target
    int _cost; //current cost from start to target
    int _total; //cost + heuristic
    PathNode *_parent;//not Java, pointers are not universal
    
    
    
    
};




#endif /* defined(__gauntmore_macosx__PathNode__) */
