//
//  NodeArray.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/26/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__NodeArray__
#define __gauntmore_macosx__NodeArray__

#include <stdio.h>
#include "PathNode.h"
class NodeArray {
public:
    NodeArray();
    ~NodeArray();
    void push_back(PathNode*);
    PathNode* pop_back();
    bool isEmpty();
    void setFront(PathNode*);
    PathNode* getFront();
    PathNode* getBack();
    int getSize();
    void swap(int, int);
    bool compare(int, int);
    
private:
    int max;
    PathNode theHeap[1000];
    void expand();
    int size;
    
};



/*
 push back
 pop back
 is empty
 
 setFront
 getFront
 getBack
 getSize
 swap(int, int)
 
 */



#endif /* defined(__gauntmore_macosx__NodeArray__) */
