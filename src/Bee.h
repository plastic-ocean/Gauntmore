#ifndef __gauntmore__Bee__
#define __gauntmore__Bee__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Bee, spBee);
class Bee : public Creature {
    
public:
    Bee();
    
    /* Virtual Methods */
    
    virtual SDL_Rect getBounds();
    virtual void damage();
    virtual void addSprite();
    virtual bool isPotion();
    
    void move();
    
private:
    Facing _facing;
    spThing _contents;
    int _speed = 100;
    spTween _moveTween;
    
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

#endif /* defined(__gauntmore__Bee__) */
