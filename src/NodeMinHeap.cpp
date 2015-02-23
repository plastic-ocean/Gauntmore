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
    this->theHeap.push_back(head);
}
NodeMinHeap::~NodeMinHeap(){}

void NodeMinHeap::insertNode( PathNode node ) {
    this->theHeap.push_back(node);
    bubbleUp( (int)theHeap.size() - 1 );
    
}

PathNode NodeMinHeap::getMinNode() {
    PathNode temp = theHeap.front();//copy head to temp
    theHeap[0] = theHeap.back();//copy last to head
    theHeap.pop_back();//remove last
    filterDown(0);//fix heap
    
    return temp;//return old head
}

void NodeMinHeap::swap(int a, int b) {
    PathNode temp = theHeap[a];
    theHeap[a] = theHeap[b];
    theHeap[b] = temp;
}



void NodeMinHeap::bubbleUp(int pos) {
    if ( pos == 0 ) return;
    int parent = (int)(pos/2);
    if ( theHeap[parent].getTotal() > theHeap[pos].getTotal() ) {
        swap(parent, pos);
    }
    bubbleUp(parent);
}

void NodeMinHeap::filterDown(int pos) {
    
    //check if you are out of scope
    int child = (pos*2);
    if (theHeap.size() - 1 < child ) return;
    else if ( theHeap.size() - 1 < (child+1) ) {
        if ( theHeap[pos].getTotal() > theHeap[child].getTotal() ) {
            swap(pos, child);
        }
        return; //one child, so you are at the bottom of the heap
    }
    
    //find smallest of left and right children
    
    if ( child > (child+1) ) child++;
    if ( theHeap[pos].getTotal() < theHeap[child].getTotal() ) {
        swap(pos, child);
        filterDown(child);
    }
    
    
    
    
    
}