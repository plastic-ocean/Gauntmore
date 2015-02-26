#ifndef __gauntmore__Slime__
#define __gauntmore__Slime__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Slime, spSlime);
class Slime : public Creature {
    
public:
    Slime();
    
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

#endif /* defined(__gauntmore__Slime__) */
