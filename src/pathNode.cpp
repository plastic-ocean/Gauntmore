//
//  pathNode.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/17/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "pathNode.h"

pathNode::pathNode( Vector2 location, int cost, int heuristic ) {
    this->location = location;
    this->cost = cost;
    this->heuristic = heuristic;
}
pathNode::~pathNode(){}

const Vector2 pathNode::getLocation(){
    return this->location;
}
const int pathNode::getHeuristic() {
    return this->heuristic;
}
const int pathNode::getCost() {
    return this->cost;
}
const int pathNode::getTotal()  {
    return this->total;
}
void pathNode::setCost( int cost ) {
    this->cost = cost; //I still dont like this much
}

void pathNode::setLocation( Vector2 location ) {
    this->location = location;
}

void pathNode::setHeuristic( int heuristic ) {
    this->heuristic = heuristic;
}

void pathNode::calculateTotal() {
    this->total = cost + heuristic;
}
pathNode pathNode::getParent() {
    return *parent;
}

void pathNode::setParent( pathNode parent ) {
    this->parent = &parent;
}
bool pathNode::operator>(pathNode &node ) {
    return this->cost > node.cost;
}

