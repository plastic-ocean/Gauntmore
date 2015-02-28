#ifndef __gauntmore_macosx__NodeMinHeap__
#define __gauntmore_macosx__NodeMinHeap__

#include <iostream>
#include <vector>
#include "PathNode.h"
#include "NodeArray.h"

class NodeMinHeap {
public:
    NodeMinHeap();
    NodeMinHeap(PathNode);
    ~NodeMinHeap();
    void insertNode(PathNode*);
    PathNode &getMinNode();
    bool empty();
    void clearHeap();
    
protected:
    void bubbleUp(int);
    void filterDown(int);
    void swap(int,int);
        NodeArray theHeap;

    
    
};





#endif /* defined(__gauntmore_macosx__NodeMinHeap__) */
