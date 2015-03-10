#ifndef __gauntmore__Potion__
#define __gauntmore__Potion__

#include "Thing.h"

DECLARE_SMART(Potion, spPotion);
class Potion: public Thing {
    
public:
    Potion();
    
    /**
     *  Gets bounds of the unit Potion.
     *  @return: SDL_Rect _bounds which is the bounds of Potion.
     */
    SDL_Rect getBounds();
    
    /**
     *  Adds Sprite and attaches it to the game.
     */
    virtual void addSprite();
    
private:
    /**
     * Initializes position and sprite of Potion. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Interaction method for Potion.
     */
    void _interact();
    
    /**
     * Updates the Potion every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Potion__) */
