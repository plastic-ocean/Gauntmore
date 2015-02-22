//
//  CollisionDetector.h
//  gauntmore_macosx
//
//  Created by benjamin barnes on 2/21/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(CollisionDetector, spCollisionDetector)
class CollisionDetector : public Object{
public:
    CollisionDetector();
    bool detectWalls(std::vector<SDL_Rect> tiles, int x, int y, int h, int w);
    bool detectUnits(std::list<spUnit> units, int x, int y, int h, int w);
private:
};




