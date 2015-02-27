//
//  NodeArray.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/26/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "NodeArray.h"

NodeArray::NodeArray() {
    max = 10;
    size = 0;
    Vector2 vec = {0,0};
    for (int i = 0;i<1000;i++) {
        theHeap[i] = PathNode(vec,9999,9999);
    }
    
    
    
}
NodeArray::~NodeArray() {
    
}

void NodeArray::push_back(PathNode *node) {
    theHeap[size++] = *node;
    
}
PathNode NodeArray::pop_back() {
    return theHeap[--size];
}

bool NodeArray::isEmpty() {
    return size==0;
}

void NodeArray::setFront(PathNode node) {
    theHeap[0] = node;
}

PathNode* NodeArray::getFront() {
    
    return &theHeap[0];
}

PathNode NodeArray::getBack() {
    return theHeap[size-1];
}
int NodeArray::getSize() {
    return size;
}

void NodeArray::swap(int a, int b) {
    PathNode temp = theHeap[a];
    theHeap[a] = theHeap[b];
    theHeap[b] = temp;
}

bool NodeArray::compare(int a, int b) {
    return theHeap[a].getTotal() > theHeap[b].getTotal();
}

void NodeArray::expand() {
    
}











