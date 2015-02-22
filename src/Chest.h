#ifndef __gauntmore__Chest__
#define __gauntmore__Chest__

#include "Thing.h"
#include "Potion.h"
#include "Gold.h"

using namespace std;

DECLARE_SMART(Chest, spChest);
class Chest: public Thing {
    
public:
    Chest();
    
    
private:
    spThing _contents;
    bool _isOpen;

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

#endif /* defined(__gauntmore__Chest__) */
