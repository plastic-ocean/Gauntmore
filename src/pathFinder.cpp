//
//  pathFinding.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//
#include <queue>
#include <cmath>
#include "pathFinder.h"
#include "game.h"
#include "pathNode.h"
#include "Collision.h"

/*
        basic implementation of A* pathfinding algorithm
 
 1. calculate heuristic from target to current node using manhattan method. This will create an inadmissible heuristic
 but we are more concerned with fast pathfinding, not the shortest possible path
 
 
 2. build a min-heap of adjacent nodes using the Total Expected cost (distance travelled from start point + estimated remaining distance via heuristic)
 
 3. Once target is hit, follow chain of pointers back to start, storing each location in a stack.
 
 4. Pop stack into tweenQueue and fire animation
 
 
 
 */
pathFinder::pathFinder(Vector2 start, Vector2 finish ) {
    this->location = start;
    this->target = finish;
    
}

void pathFinder::aStar() {
    pathNode start = *new pathNode( location, 0, findHeuristic(location), start );
    openList.push(start);
    
    
    while ( !openList.empty() ) {
        //do things here
        closedList.push_back(openList.top() );
        openList.pop();
        scanSurround( closedList.back() );
    }
    
    
}

int pathFinder::findHeuristic( Vector2 curLoc ) {
    return abs( curLoc.x - this->target.x ) + abs( curLoc.y - this->target.y );
}

void pathFinder::scanSurround( pathNode node ) {
    Vector2 temp = node.getLocation() ;
    temp.x -= mapSize;
    temp.y -= mapSize;
    int summ = 12;//something more clever goes here
    int flip = -2;
    
        //check for collision
        //check for existence in closedList
    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j < 2; j++ ) {
            flip *= (-1);
            if (!inClosedList(node) ) {
                openList.push(*new pathNode(temp,node.getTotal()+(summ+flip),findHeuristic(temp), node ) );
            }
            temp.x += mapSize;
        }
        temp.x -= 3*mapSize;
        temp.y += mapSize;
    }

    
}

bool pathFinder::inClosedList( pathNode node ) {
    int size = closedList.size();
    for (int i = 0; i<size;i++ ) {
        if ( closedList[i].getLocation() == node.getLocation() ) return true;
    }
    return false;
    
}




