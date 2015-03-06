#ifndef __gauntmore__Skeleton__
#define __gauntmore__Skeleton__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Skeleton, spSkeleton);
class Skeleton : public Creature {
    
public:

    /**
     *
     *
     */
    Skeleton();
    
    /**
     *
     *
     */
    virtual SDL_Rect getBounds();
    
    /**
     *
     *
     */
    virtual bool isPotion();
    
    virtual void addSprite();
    virtual void damage();
    
    
    
private:
    Facing _facing;
    
    spThing _contents;
    
    /**
     * Initializes position and sprite of Skeleton. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Interaction method for Skeleton.
     */
    void _interact();
    
    void move();
    
    void attack();
    
    /**
     * Updates the Skeleton every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Skeleton__) */
