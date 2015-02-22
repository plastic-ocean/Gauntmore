#ifndef __gauntmore__Potion__
#define __gauntmore__Potion__

#include "Thing.h"

DECLARE_SMART(Potion, spPotion);
class Potion: public Thing {
    
public:
    Potion();
    
    /**
     * Interaction method for Potion.
     */
    void interact();
    
private:
    /**
     * Initializes position and sprite of Potion. Called by Unit's init() method.
     */
    void _init();
    
    
    
    /**
     * Updates the Potion every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Potion__) */
