#ifndef __gauntmore__Skeleton__
#define __gauntmore__Skeleton__

#include "Creature.h"

DECLARE_SMART(Skeleton, spSkeleton)
class Skeleton : public Creature{
public:
    Skeleton();

private:
    void _init();
    
    void _interact();
    
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Skeleton__) */
