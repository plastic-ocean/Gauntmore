//
//  GreaterThan.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/18/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "GreaterThan.h"
bool GreaterThan::operator()(pathNode &a, pathNode &b ) {
    return a.getCost() > b.getCost(); 
}