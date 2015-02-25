//
//  pathFinding.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//
#include <queue>
#include <cmath>
#include "PathFinder.h"
#include "game.h"
#include "PathNode.h"

/*
        basic implementation of A* pathfinding algorithm
 
 1. calculate heuristic from target to current node using manhattan method. This will create an inadmissible heuristic
 but we are more concerned with fast pathfinding, not the shortest possible path
 
 
 2. build a min-heap of adjacent nodes using the Total Expected cost (distance travelled from start point + estimated remaining distance via heuristic)
 
 3. Once target is hit, follow chain of pointers back to start, storing each location in a stack.
 
 4. Pop stack into tweenQueue and fire animation
 
 
 
 */
PathFinder::PathFinder() {
    openList = new NodeMinHeap();
}

PathFinder::~PathFinder() {
    
}

vector<Vector2> PathFinder::aStar(Vector2 start, Vector2 finish ) {
    PathNode first = *new PathNode( start, 0, findHeuristic(start) );
    this->target = finish;
    this->source = start;
    openList->insertNode(first);//add start to heap
    
    
    while ( !openList->empty() ) {
        
        PathNode temp = openList->getMinNode();//pop smallest from heap
        if ( atExit(temp) ) {//are we at the exit?
           return makePath( temp );
            
        }
        closedList.push_back( temp );//put node in closed list
        scanSurround( closedList.back() );//add surrounding nodes to open list
    }
    //if you got here, there is no path to the target.
    vector<Vector2> nullVector;
    return nullVector;
    
}

int PathFinder::findHeuristic( Vector2 curLoc ) {
    return abs( curLoc.x - this->target.x ) + abs( curLoc.y - this->target.y );
}


void PathFinder::scanSurround( PathNode node ) {
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
                openList->insertNode(*new PathNode( temp,node.getTotal()+(summ+flip), findHeuristic(temp), node ) );
            }
            temp.x += mapSize;
        }
        temp.x -= 3*mapSize;
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



bool PathFinder::inClosedList( PathNode node ) {
    int size = (int)closedList.size();
    for (int i = 0; i<size;i++ ) {
        if ( closedList[i].getLocation() == node.getLocation() ) return true;
    }
    return false;
    
}

vector<Vector2> PathFinder::makePath(PathNode node ) {
    vector<Vector2> tempVect;

    while (node.getLocation() != source ) {
        tempVect.push_back( node.getLocation() );
        node = node.getParent();
        }
    return tempVect;
}




