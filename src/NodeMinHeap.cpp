#include "NodeMinHeap.h"


/*
Default Constructor
 */
NodeMinHeap::NodeMinHeap() {
    //default constructor, do nothing
}


/*
 Destructor
 */
NodeMinHeap::~NodeMinHeap(){}


/*
 Adds a node to the openlist
 @node is a pointer to the node to be inserted
 */
void NodeMinHeap::insertNode( PathNode *node ) {
    if ( theHeap.getSize() < 999 ){
        theHeap.push_back(node);
        bubbleUp( theHeap.getSize()-1 );
    }
}


/*
 empties the heap to allow for a clean slate
 */
void NodeMinHeap::clearHeap() {
    NodeArray newArray = NodeArray();
    
    theHeap = newArray;
    
}


/*
 Returns the root of the minHeap
 */
PathNode NodeMinHeap::getMinNode() {
    
    PathNode temp = *theHeap.getFront();//copy head to temp
    theHeap.setFront(theHeap.pop_back() );//copy last to head
    filterDown(0);//fix heap
    
    return temp;//return old head
}


/*
 Returns the number of elements in the heap
 */
int NodeMinHeap::getSize() {
    return theHeap.getSize();
}


/*
 Checks if the heap is empty
 */
bool NodeMinHeap::empty() {
    return theHeap.getSize() == 0;
}


/*
 Moves a node from the bottom of the heap to it's proper place
 @pos is the location in the heap of the node being bubbled
 */
void NodeMinHeap::bubbleUp(int pos) {
    if ( pos == 0 ) return;
    int parent = (pos/2);
    if (theHeap.compare(parent, pos) ) {
        theHeap.swap(parent, pos);
    }
    bubbleUp(parent);
}


/*
 takes a node at the 'top' of the heap, and has it sink to it's proper level
 @pos is location of the node in the heap
 */
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
