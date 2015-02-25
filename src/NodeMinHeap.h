//
//  NodeMinHeap.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/23/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__NodeMinHeap__
#define __gauntmore_macosx__NodeMinHeap__

#include <stdio.h>
#include "PathNode.h"
#include "Game.h"
class PathNode;
class NodeMinHeap {
public:
    NodeMinHeap();
    NodeMinHeap(PathNode);
    ~NodeMinHeap();
    void insertNode(PathNode);
    PathNode getMinNode();
    bool empty();

    
private:
    std::vector<PathNode> theHeap;
    void bubbleUp(int);
    void filterDown(int);
    void swap(int,int);
    
    
    
    
};





#endif /* defined(__gauntmore_macosx__NodeMinHeap__) */
