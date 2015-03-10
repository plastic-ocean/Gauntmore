#pragma once

#include "Thing.h"
#include "Potion.h"
#include "Gold.h"
#include "Armor.h"

using namespace std;

DECLARE_SMART(Chest, spChest);
class Chest: public Thing {
    
public:
    Chest();
    
    /**
     *  Gets bounds of a chest.
     *  @return: A SDL_Rect which is the bounds of a chest.
     */
    virtual SDL_Rect getBounds();
    
    /**
     * Adds sprite and attachs it to the game.
     */
    virtual void addSprite();
    
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
     *  Sets the contents of a chest to either a Potion or Gold.
     */
    void _setContents();
    
    /**
     * Updates the Chest every frame. Called by Units update() method.
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};