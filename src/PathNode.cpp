#include "PathNode.h"


/*
Default Constructor
 */
PathNode::PathNode(){
    this->_location = {0,0};
    this->_heuristic = 99999;
    this->_total = 99999;
    this->_cost = 99999;
    this->_parent = NULL;
}


/*
Constructor for 'root' node
 parent pointer goes to null
 */
PathNode::PathNode( Vector2 location, int cost, int heuristic ) {//loopback constructor
    this->_location = location;
    this->_cost = cost;
    this->_heuristic = heuristic;
    this->_parent = NULL;
    this->_total = cost + heuristic;
}


/*
 Overloaded Constructor
 */
PathNode::PathNode( Vector2 location, int cost, int heuristic, PathNode *parent ) {
    this->_location = location;
    this->_cost = cost;
    this->_heuristic = heuristic;
    this->_parent = parent;
    this->_total = cost + heuristic;
}


/*
 Destructor
 */
PathNode::~PathNode(){}

const Vector2 PathNode::getLocation(){
    
    return this->_location;
}
const int PathNode::getHeuristic() {
    return this->_heuristic;
}
const int PathNode::getCost() {
    return this->_cost;
}
const int PathNode::getTotal()  {
    return _total;
}
void PathNode::setCost( int cost ) {
    this->_cost = cost;
}

void PathNode::setLocation( Vector2 location ) {
    this->_location = location;
}

void PathNode::setHeuristic( int heuristic ) {
    this->_heuristic = heuristic;
}

PathNode* PathNode::getParent() {
    return this->_parent;
}

void PathNode::setParent( PathNode *parent ) {
    this->_parent = parent;
}
