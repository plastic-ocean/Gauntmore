//
//  CreatureMover.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/24/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "CreatureMover.h"


CreatureMover::CreatureMover() {

}

CreatureMover::~CreatureMover() {
}

bool CreatureMover::isEmpty() {
    return thePath.empty();
}

bool CreatureMover::updatePath(vector<Vector2> newPath) {
    //    if (thePath.size() == 0 ) {
    this->thePath = newPath; //maybe add some clever stuff here later
    return true;
    //    }
    //    else {
    //
    //    }
    //    return false;
}

Vector2 CreatureMover::peekNext() {
    return thePath.back();
}

Vector2 CreatureMover::popNext() {
    Vector2 temp = thePath.back();
    thePath.pop_back();
    return temp;

}


