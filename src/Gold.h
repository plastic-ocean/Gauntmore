#ifndef __gauntmore__Gold__
#define __gauntmore__Gold__

#include "Thing.h"

DECLARE_SMART(Gold, spGold);
class Gold: public Thing {
    
public:
    Gold();
    
private:
    /**
     * Initializes position and sprite of Gold. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Interaction method for Gold.
     */
    void _interact();
        
    /**
     * Updates the Gold every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Gold__) */
