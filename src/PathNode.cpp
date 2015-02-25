//
//  PathNode.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "PathNode.h"

PathNode::PathNode( Vector2 location, int cost, int heuristic ) {
    this->location = location;
    this->cost = cost;
    this->heuristic = heuristic;
}

PathNode::~PathNode(){}

Vector2 PathNode::getLocation(){
    return this->location;
}

int PathNode::getHeuristic() {
    return this->heuristic;
}

int PathNode::getCost() {
    return this->cost;
}

const int PathNode::getTotal()  {
    return this->total;
}

void PathNode::setCost( int cost ) {
    this->cost = cost; //I still dont like this much
}

void PathNode::setLocation( Vector2 location ) {
    this->location = location;
}

void PathNode::setHeuristic( int heuristic ) {
    this->heuristic = heuristic;
}

void PathNode::calculateTotal() {
    this->total = cost + heuristic;
}

PathNode PathNode::getParent() {
    return *parent;
}

void PathNode::setParent( PathNode parent ) {
    this->parent = &parent;
}


