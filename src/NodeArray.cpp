#include "NodeArray.h"


/*
 Default Constructor
 */
NodeArray::NodeArray():size(0) {
    Vector2 vec = {0,0};
    for (int i = 0;i<1000;i++) {
        theHeap[i] = PathNode(vec,9999,9999);
    }
}


/*
 Destructor
 */
NodeArray::~NodeArray() {
    
}


/*
 places node at back of array
 */
void NodeArray::push_back(PathNode *node) {
    theHeap[size] = *node;
    if (size < 1000) {
        size++;
    }
}


/*
 removes last item from array
 */
PathNode* NodeArray::pop_back() {
    return &theHeap[--size];
}


/*
 Returns whether the array is empty
 */
bool NodeArray::isEmpty() {
    return size==0;
}

void NodeArray::setFront(PathNode *node) {
    theHeap[0] = *node;
}


PathNode* NodeArray::getFront() {
    return &theHeap[0];
}


PathNode* NodeArray::getBack() {
    return &theHeap[size-1];
}


int NodeArray::getSize() {
    return size;
}


/*
 Swap node at location @a in array with location @b in array
 */
void NodeArray::swap(int a, int b) {
    PathNode temp = theHeap[a];
    theHeap[a] = theHeap[b];
    theHeap[b] = temp;
}


/*
 true if node @a is larger than node @b
 */
bool NodeArray::compare(int a, int b) {
    return theHeap[a].getTotal() > theHeap[b].getTotal();
}












