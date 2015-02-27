//
//  NodeMinHeap.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/23/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "NodeMinHeap.h"

NodeMinHeap::NodeMinHeap() {
    //default constructor, do nothing
}

NodeMinHeap::NodeMinHeap( PathNode head ) {
}

NodeMinHeap::~NodeMinHeap(){}

void NodeMinHeap::insertNode( PathNode *node ) {
    Vector2 vec = {0,0};
//    PathNode temp = node;
    
    theHeap.push_back(node);
    bubbleUp( theHeap.getSize() );
    
}

PathNode* NodeMinHeap::getMinNode() {
    PathNode *temp = theHeap.getFront();//copy head to temp
    theHeap.setFront(theHeap.getBack() );//copy last to head
    theHeap.pop_back();//remove last
    filterDown(0);//fix heap
    
    return temp;//return old head
}




void NodeMinHeap::bubbleUp(int pos) {
    if ( pos == 0 ) return;
    int parent = (int)(pos/2);
    if (theHeap.compare(parent, pos) ) {  //if ( theHeap[parent].getTotal() > theHeap[pos].getTotal() ) {
        theHeap.swap(parent, pos);
    }
    bubbleUp(parent);
}

bool NodeMinHeap::empty() {
    return theHeap.getSize() == 0;
}

void NodeMinHeap::filterDown(int pos) {
    
    //check if you are out of scope
    int child = (pos*2);
    if ( theHeap.getSize() - 1 < child ) return;
    else if ( theHeap.getSize() - 1 < (child+1) ) {
        if (theHeap.compare(pos, child) ) {        //if ( theHeap[pos].getTotal() > theHeap[child].getTotal() ) {
            theHeap.swap(pos, child);
        }
        return; //one child, so you are at the bottom of the heap
    }
    
    //find smallest of left and right children
    
    if ( child > (child+1) ) child++;
    if (theHeap.compare(child, pos) ) {        //if ( theHeap[child].getTotal() > theHeap[pos].getTotal() ) {
        theHeap.swap(child, pos);
        filterDown(child);
    }
    
    
    
    
    
}