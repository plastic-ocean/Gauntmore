#ifndef __gauntmore__Ghost__
#define __gauntmore__Ghost__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Ghost, spGhost);
class Ghost : public Creature {
    
public:
    Ghost();
    
    /* Virtual Methods */
    
    virtual SDL_Rect getBounds();
    virtual void addSprite();
    virtual bool isPotion();
    
    void move();
    
private:
    Facing _facing;
    spThing _contents;
    spTween _moveTween;
    
    /**
     * Initializes position and sprite of Chest. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Updates the Chest every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
//    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Ghost__) */
