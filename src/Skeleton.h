//
//  Skeleton.h
//  gauntmore_macosx
//
//  Created by benjamin barnes on 2/14/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

//#ifndef __gauntmore_macosx__Skeleton__
//#define __gauntmore_macosx__Skeleton__

#include <stdio.h>
#include "Creature.h"

DECLARE_SMART(Skeleton, spSkeleton)
class Skeleton : public Creature{
public:
    Skeleton();

private:
    void _init();
    void _update(const UpdateState &us);
};

//#endif /* defined(__gauntmore_macosx__Skeleton__) */
