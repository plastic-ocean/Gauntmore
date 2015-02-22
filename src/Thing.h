#include "Unit.h"

#ifndef __gauntmore__Thing__
#define __gauntmore__Thing__

DECLARE_SMART(Thing, spThing);
class Thing: public Unit {
    
public:
    Thing();
    
    /**
     * Interaction method for Thing.
     * Method is Virtual and will be defined elsewhere.
     */
    virtual void interact();
    
protected:
    
    bool _open;
    
    /**
     * Initializes position and sprite of Thing. Called by Unit's init() method.
     */
    void _init();
    
    
    
    /**
     * Updates the Thing every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Thing__) */
