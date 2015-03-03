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
    
    theHeap.push_back(node);
    bubbleUp( theHeap.getSize()-1 );
    
}

void NodeMinHeap::clearHeap() {
    NodeArray newArray = NodeArray();
    
    theHeap = newArray;
    
}


PathNode NodeMinHeap::getMinNode() {
    
    PathNode temp = *theHeap.getFront();//copy head to temp
    theHeap.setFront(theHeap.pop_back() );//copy last to head
    filterDown(0);//fix heap
    
    return temp;//return old head
}




void NodeMinHeap::bubbleUp(int pos) {
    if ( pos == 0 ) return;
    int parent = (pos/2);
    if (theHeap.compare(parent, pos) ) {
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
    if (pos == 0) child = 1;
    if ( theHeap.getSize()-1 < child ) return;
    else if ( theHeap.getSize()-1 < (child+1) ) {
        if (theHeap.compare(pos, child) ) {
            theHeap.swap(pos, child);
        }
        return; //one child, so you are at the bottom of the heap
    }
    
    //find smallest of left and right children
    
    if ( theHeap.compare(child, child+1) ) child++;
    if (theHeap.compare(child, pos) ) {
        theHeap.swap(child, pos);
        filterDown(child);
    }
    
    
    
    
    
}