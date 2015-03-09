#ifndef __gauntmore_macosx__NodeMinHeap__
#define __gauntmore_macosx__NodeMinHeap__

#include <iostream>
#include <vector>

#include "PathNode.h"
#include "NodeArray.h"

class NodeMinHeap {
public:
    NodeMinHeap();
    
    ~NodeMinHeap();
    
    /*
     Adds a node to the openlist
     @node is a pointer to the node to be inserted
     */
    
    void insertNode(PathNode*);
    
    /*
     empties the heap to allow for a clean slate
     */
    
    void clearHeap();
    
    /*
     Returns the root of the minHeap
     */
    
    PathNode getMinNode();
    
    /*
     Returns the number of elements in the heap
     */
    
    int getSize();
    
    /*
     Checks if the heap is empty
     */
    
    bool empty();
    
    
    
protected:
    NodeArray theHeap;
    
    /*
     Moves a node from the bottom of the heap to it's proper place
     @pos is the location in the heap of the node being bubbled
     */
    
    void bubbleUp(int);
    
    /*
     takes a node at the 'top' of the heap, and has it sink to it's proper level
     @pos is location of the node in the heap
     */
    
    void filterDown(int);

    
    
};





#endif /* defined(__gauntmore_macosx__NodeMinHeap__) */
