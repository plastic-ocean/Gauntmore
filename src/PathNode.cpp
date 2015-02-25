//
//  PathNode.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "PathNode.h"

PathNode::PathNode(){}

PathNode::PathNode( Vector2 location, int cost, int heuristic ) {
    this->location = location;
    this->cost = cost;
    this->heuristic = heuristic;
    this->parent = this;
}


PathNode::PathNode( Vector2 location, int cost, int heuristic, PathNode parent ) {
    this->location = location;
    this->cost = cost;
    this->heuristic = heuristic;
    this->parent = &parent;
}
PathNode::~PathNode(){}

const Vector2 PathNode::getLocation(){
    return this->location;
}
const int PathNode::getHeuristic() {
    return this->heuristic;
}
const int PathNode::getCost() {
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
//bool PathNode::operator>(PathNode &node ) {
//    return this->cost > node.cost;
//}
