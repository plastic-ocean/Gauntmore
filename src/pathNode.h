//
//  pathNode.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__pathNode__
#define __gauntmore_macosx__pathNode__

#include <stdio.h>
#include "Map.h"
#include "Creature.h"
#include "Game.h"

class pathNode {
public:
    pathNode( Vector2, int, int );
    ~pathNode();
    Vector2 getLocation();
    int getHeuristic();
    int getCost();
    int getTotal();
    void setHeuristic(int);
    void setCost(int);
    void calculateTotal();
    void setLocation(Vector2);
    bool operator>(  pathNode& node );
    pathNode getParent();
    void setParent(pathNode);
    
private:
    Vector2 location;
    int heuristic; //estimated cost from current to target
    int cost; //current cost from start to target
    int total; //cost + heuristic
    pathNode *parent;//not Java, pointers are not universal
    
    
    
    
};




#endif /* defined(__gauntmore_macosx__pathNode__) */
