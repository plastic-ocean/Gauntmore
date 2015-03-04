#ifndef __gauntmore__Skeleton__
#define __gauntmore__Skeleton__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Skeleton, spSkeleton);
class Skeleton : public Creature {
    
public:
    Skeleton();
    
    /**
     *  Gets bounds of the unit Skeleton.
     *  @return: SDL_Rect _bounds which is the bounds of Skeleton.
     */
    virtual SDL_Rect getBounds();
    
    /**
     *  Boolean method to determine if the unit is a Potion.
     */
    virtual bool isPotion();
    
private:
    spThing _contents;
    
    /**
     * Initializes position and sprite of Skeleton. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Interaction method for Skeleton.
     */
    void _interact();
    
    /**
     * Updates the Skeleton every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Skeleton__) */
