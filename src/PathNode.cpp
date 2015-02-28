#include "PathNode.h"

PathNode::PathNode(){
    this->location = {0,0};
    this->heuristic = 9999;
    this->total = 9999;
    this->cost = 9999;
    this->parent = NULL;
}

PathNode::PathNode( Vector2 location, int cost, int heuristic ) {//loopback constructor
    this->location = location;
    this->cost = cost;
    this->heuristic = heuristic;
    this->parent = NULL;
    this->total = cost + heuristic;
}


PathNode::PathNode( Vector2 location, int cost, int heuristic, PathNode *parent ) {
    this->location = location;
    this->cost = cost;
    this->heuristic = heuristic;
    this->parent = parent;
    this->total = cost + heuristic;
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
    return total;
}
void PathNode::setCost( int cost ) {
    this->cost = cost;
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
PathNode* PathNode::getParent() {
    return this->parent;
}

void PathNode::setParent( PathNode *parent ) {
    this->parent = parent;
}
