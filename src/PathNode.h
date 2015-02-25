<<<<<<< HEAD:src/PathNode.h
//
//  PathNode.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__PathNode__
#define __gauntmore_macosx__PathNode__

#include <stdio.h>
=======
#ifndef __gauntmore__pathNode__
#define __gauntmore__pathNode__

>>>>>>> origin/keith:src/PathNode.h
#include "Map.h"
#include "Creature.h"
#include "Game.h"

class PathNode {
public:
<<<<<<< HEAD:src/PathNode.h
    PathNode();
    PathNode( Vector2, int, int );
    PathNode( Vector2, int, int, PathNode );
    ~PathNode();
    const Vector2 getLocation();
    const int getHeuristic();
    const int getCost();
=======
    PathNode( Vector2, int, int );
    ~PathNode();
    Vector2 getLocation();
    int getHeuristic();
    int getCost();
>>>>>>> origin/keith:src/PathNode.h
    const int getTotal();
    void setHeuristic(int);
    void setCost(int);
    void calculateTotal();
    void setLocation(Vector2);
<<<<<<< HEAD:src/PathNode.h
//    bool operator>(  PathNode& node );
=======
//    bool operator >(  pathNode& node );
>>>>>>> origin/keith:src/PathNode.h
    PathNode getParent();
    void setParent(PathNode);
    
private:
    Vector2 location;
    int heuristic; //estimated cost from current to target
    int cost; //current cost from start to target
    int total; //cost + heuristic
    PathNode *parent;//not Java, pointers are not universal
    
    
    
    
};




#endif /* defined(__gauntmore_macosx__PathNode__) */
