#ifndef __gauntmore__Skeleton__
#define __gauntmore__Skeleton__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Skeleton, spSkeleton);
class Skeleton : public Creature {
    
public:
    Skeleton();
    
    virtual SDL_Rect getBounds();
    
    virtual bool isPotion();
    
private:
    spThing _contents;
    
    /**
     * Initializes position and sprite of Chest. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Interaction method for Chest.
     */
    void _interact();
    
    /**
     * Updates the Chest every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Skeleton__) */
